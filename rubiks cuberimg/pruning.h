#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <fstream>

#include "symmetries.h"
#include "cubie.h"

std::vector <unsigned short> flipslice_twist_depth3{};
std::vector <unsigned short> corners_ud_edges_depth3{};


//This is meant to give exactly the number of moves mod 3 to solve this cube in phase 1
//Im not sure how though but this is what Kociemba states on his site
unsigned int get_flipslice_twist_depth_3(unsigned int index) {
	unsigned int y = flipslice_twist_depth3[index / 16];
	y >>= (index % 16) * 2;
	return y & 3;
}


//This is meant to give at the least the number of moves to solve phase 2
unsigned int get_corners_ud_edges_depth_3(unsigned int index) {
	unsigned int y = corners_ud_edges_depth3[index / 16];
	y >>= (index % 16) * 2;
	return y & 3;
}

void set_flipslice_twist_depth3(unsigned int index, unsigned int value) {
	unsigned int shift = (index % 16) * 2;
	unsigned int base = index >> 4;
	flipslice_twist_depth3[base] &= ~(3 << shift) & 0xffffffff;
	flipslice_twist_depth3[base] |= value << shift;
}

void set_corners_ud_edges_depth3(unsigned int index, unsigned int value) {
	unsigned int shift = (index % 16) * 2;
	unsigned int base = index >> 4;
	corners_ud_edges_depth3[base] &= ~(3 << shift) & 0xffffffff;
	corners_ud_edges_depth3[base] |= value << shift;
}


void make_phase_1_pruning_table() {
	const unsigned int total = 2817 * 64430;

	std::array <unsigned short, 2188> flipslice_twist_depth3{};
	cubie c;
	std::array <unsigned int, 2188> flipslice_sym{};
	flipslice_sym.fill(0);
	unsigned int sym;

	unsigned short rep = 0;
	unsigned short flip;
	unsigned short twist;
	unsigned int done;
	bool backsearch;
	unsigned short depth = 0;
	unsigned short ud_slice;
	unsigned int flipslice_class;

	unsigned int index;
	unsigned int index_new;
	unsigned short mult;
	bool match;

	unsigned short flipslice;

	unsigned short flipslice_new;
	unsigned short twist_new;
	unsigned short flip_new;
	unsigned short ud_slice_new;

	unsigned short flipslice_class_new;
	unsigned short flipslice_symmetry_new;


	std::array <cubie, 48> symmetries = gen_symmetries();
	std::array <cubie, 48> inv_symmetries = gen_inv_symmetries(symmetries);
	cubie sy;


	for (unsigned int i; i != (64430 * 2187) / 16 + 1; i++) {
		flipslice_twist_depth3.push_back(0xffffffff);
	}

//All the files needed for this function
	std::ifstream twist_table;
	twist_table.open("twist move table.bin");

	std::ifstream flip_table;
	twist_table.open("flip move table.bin");

	std::ifstream ud_slice_table;
	twist_table.open("ud slice phase 2 move table.bin");

	std::ifstream flipslice_sym_class;
	flipslice_sym_class.open("flipslice sym class table.bin");

	std::ifstream flipslice_sym_rep;
	flipslice_sym_class.open("flipslice sym rep table.bin");

	std::ifstream flipslice_symmetry;
	flipslice_sym_class.open("flipslice symmetry table.bin");


	for (unsigned short i; i != 64430; i++) {
		flipslice_sym_rep.seekg(2 * i);
		flipslice_sym_rep.read((char*)&rep, 2);

		flip = rep % 2187;
		ud_slice = rep / 2187;

		c.set_ud_slice_phase_1(ud_slice);
		c.set_flip(flip);

		for (short s = 0; s != 16; s++) {
			sy = symmetries[s];
			sy.edge_multiply(c);
			sy.multiply(inv_symmetries[s]);
			if (c.get_ud_slice_phase_1() == ud_slice && c.get_flip() == flip) {
				flipslice_sym[i] |= 1 << s; //This is essentially the same as setting
				// to 2^s
			}
		}

		flipslice_class = 0;
		twist = 0;

		set_flipslice_twist_depth3(2187 * flipslice_class + twist, 0);

		done = 1;
		depth = 0;
		backsearch = false;

		while (done != 64430 * 2187) {
			depth = depth % 3;


			if (depth == 9) { backsearch = true; }
			if (depth < 8) { mult = 5; }
			else { mult = 1; }

			index = 0;



			while (flipslice_class != 64430) {
				twist = 0;
				while (twist < 2187) {
					if (backsearch == false
						&& index % 16 == 0
						&& flipslice_twist_depth3[index % 16] == 0xffffffff
						&& twist < 2187 - 16) {
						twist += 16;
						index += 16;
						flipslice_class++;
						break;
					}

					if (backsearch == true) { match = (get_flipslice_twist_depth_3(index) == 3); }
					else { match = (get_flipslice_twist_depth_3(index) == depth % 3); }

					if (match == true) {
						flipslice_sym_rep.seekg(2 * flipslice_class);
						flipslice_sym_rep.read((char*)&flipslice, sizeof(unsigned short));
						flip = flipslice % 2048;
						ud_slice = flipslice >> 11; //This is the same as div 2048 but faster

						for (unsigned short m = 0; m != 18; m++) {

							twist_table.seekg(2 * (18 * twist + m));
							twist_table.read((char*)&twist_new, sizeof(unsigned short));

							flip_table.seekg(2 * (18 * flip + m));
							flip_table.read((char*)&flip_new, sizeof(unsigned short));

							ud_slice_table.seekg(2 * (432 * ud_slice + m));
							ud_slice_table.read((char*)&ud_slice_new, sizeof(unsigned short));

							flipslice_new = (ud_slice_new << 11) + flip_new;

							flipslice_sym_class.seekg(2 * (flipslice_new));
							flipslice_sym_class.read((char*)&flipslice_symmetry_new, sizeof(unsigned short));


							twist_table.seekg(2 * ((twist_new << 4) + flipslice_symmetry_new));
							twist_table.read((char*)&twist_new, 2);

							index = 2187 * flipslice_class_new + twist_new;

							if (backsearch == false) {
								if (get_flipslice_twist_depth_3(index) == 3) {
									set_flipslice_twist_depth3(index, (depth + 1) % 3);
									done++;


									//Everything below is just for dealing with symmetries
									sym = flipslice_sym[flipslice_class_new];
									if (sym != 1) { //Earlier the symmetries were declared using left shifts, 
													//here right shifts are used
													//if it's equal to one you can't right shift

										for (short i = 1; i != 16; i++) {
											sym >>= 1;
											if (sym % 2 == 1) {
												twist_table.seekg(2 * ((twist_new << 4) + i));
												twist_table.read((char*)&twist_new, 2);

												index_new = 2187 * flipslice_class_new + twist_new;
												if (get_flipslice_twist_depth_3(index_new) == 3) {
													set_flipslice_twist_depth3(index_new, (depth + 1) % 3);
													done++;
												}
											}
										}

									}
								}
							}
							else {
								if (get_flipslice_twist_depth_3(index) == depth % 3) {
									set_flipslice_twist_depth3(index, (depth + 1) % 3);
									done++;
									break;
								}
							}

						}

					}
					twist++;
					index++;
				}
			}
			depth++;

		}
	}
}