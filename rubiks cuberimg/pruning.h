#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <ctime>

#include <chrono>

#include "symmetries.h"
#include "cubie.h"

std::vector <unsigned char> flipslice_twist_depth3{};
std::vector <unsigned short> corners_ud_edges_depth3{};


std::string getTime() {
	time_t result = time(0);

	char str[26];
	ctime_s(str, sizeof str, &result);  

	return str;
}

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

unsigned short do_phase_2_move(unsigned long long moveses,
	std::vector <unsigned short> ud_edges_table,
	std::vector <unsigned short> corners_table,
	std::vector <unsigned short> corner_sym_classes,
	std::vector <unsigned short> corner_symmetry,
	std::vector <unsigned short> ud_edge_sym_conversion,
	unsigned short i) {

	unsigned int ud_edges = 0, corner = 0, ud_slice = 0;
	unsigned short m;
	unsigned int index = 0;
	unsigned int flipslice;

	unsigned short corner_sym_class = 0;
	unsigned short corner_sym;


	while (moveses != 0) {
		unsigned short m = moveses % 10;
		moveses = moveses / 10;

		ud_edges = ud_edges_table[18 * ud_edges + m];
		corner = corners_table[18 * corner + m];
		corner_sym_class = corner_sym_classes[corner];
		corner_sym = corner_symmetry[corner];

		ud_edges = ud_edge_sym_conversion[(ud_edges << 4) + corner_sym];
		////<< 4 does times 2^4 or times 16

		index = 40320 * corner_sym_class + ud_edges;



		if (corners_ud_edges_depth3[index] < i) { //if it's less than it's already filled
			return 4000000000;
		}
	}

	return index;
}

void make_phase_2_pruning_table() {

	cubie c;
	std::vector <unsigned short> corners_ud_edges_depth3{};

	for (unsigned int i = 0; i != 64430; i++) {
		corners_ud_edges_depth3.push_back(0);
	}

	unsigned int index;

	std::array <cubie, 48> symmetries = gen_symmetries();
	std::array <cubie, 48> inv_symmetries = gen_inv_symmetries(symmetries);
	cubie sy;


	for (unsigned long i = 0; i != (64430 * 2187) / 16 + 1; i++) {
		flipslice_twist_depth3.push_back(30);
	}

	//All the files needed for this function

	// -------------------------------------------------------------------------------------

	std::ifstream ud_edge_sym_conversion_f;
	ud_edge_sym_conversion_f.open("ud edges sym table.bin");

	std::vector <unsigned short> ud_edge_sym_conversion;

	for (unsigned int i = 0; i != 16 * 40320; i++) {
		ud_edge_sym_conversion.push_back(0);
	}

	for (unsigned int i = 0; i != 16 * 40320; i++) {
		ud_edge_sym_conversion_f.read((char*)&ud_edge_sym_conversion[i], sizeof(unsigned short));
	}

	ud_edge_sym_conversion_f.close();


	// -------------------------------------------------------------------------------------

	std::ifstream corners_table_f;
	corners_table_f.open("corners move table.bin");

	std::vector <unsigned short> corners_table;

	for (unsigned int i = 0; i != 40320 * 18; i++) {
		corners_table.push_back(0);
	}

	for (unsigned int i = 0; i != 40320 * 18; i++) {
		corners_table_f.read((char*)&corners_table[i], sizeof(unsigned short));
	}

	corners_table_f.close();

	// -------------------------------------------------------------------------------------

	std::ifstream ud_edges_table_f;
	ud_edges_table_f.open("ud edges move table.bin");

	std::vector <unsigned short> ud_edges_table;

	for (unsigned int i = 0; i != 40320 * 18; i++) {
		ud_edges_table.push_back(0);
	}

	for (unsigned int i = 0; i != 40320 * 18; i++) {
		ud_edges_table_f.read((char*)&ud_edges_table[i], sizeof(unsigned short));
	}

	ud_edges_table_f.close();

	// -------------------------------------------------------------------------------------

	std::ifstream corner_sym_class_f;
	corner_sym_class_f.open("corner sym class table.bin");

	std::vector <unsigned short> corner_sym_classes;

	for (unsigned int i = 0; i != 40320; i++) {
		corner_sym_classes.push_back(0);
	}

	for (unsigned int i = 0; i != 40320; i++) {
		corner_sym_class_f.read((char*)&corner_sym_classes[i], sizeof(unsigned short));
	}

	corner_sym_class_f.close();

	// -------------------------------------------------------------------------------------

	std::ifstream corner_sym_rep_table_f;
	corner_sym_rep_table_f.open("corner sym rep table.bin");

	std::vector <unsigned short> corner_sym_rep;

	for (unsigned int i = 0; i != 64430; i++) {
		corner_sym_rep.push_back(0);
	}

	for (unsigned int i = 0; i != 64430; i++) {
		corner_sym_rep_table_f.read((char*)&corner_sym_rep[i], sizeof(unsigned short));
	}

	corner_sym_rep_table_f.close();

	// -------------------------------------------------------------------------------------

	std::ifstream corner_symmetry_f;
	corner_symmetry_f.open("corner symmetry table.bin");

	std::vector <unsigned short> corner_symmetry;

	for (unsigned int i = 0; i != 2048 * 495; i++) {
		corner_symmetry.push_back(0);
	}

	for (unsigned int i = 0; i != 2048 * 495; i++) {
		corner_symmetry_f.read((char*)&corner_symmetry[i], sizeof(unsigned short));
	}

	corner_symmetry_f.close();


	// -------------------------------------------------------------------------------------


	unsigned long long total_moves;
	total_moves = 0;


	corners_ud_edges_depth3[0] = 0;

	for (unsigned short i = 1; i != 18; i++) {
		total_moves = i * total_moves + 10;

		for (unsigned long long moveses = 0; moveses != total_moves; moveses++) {
			index = do_phase_2_move(moveses, ud_edges_table, corners_table,
				corner_sym_classes, corner_symmetry, ud_edge_sym_conversion, i);
			if (index == 4000000000) {
				continue;
			}
			else if (corners_ud_edges_depth3[index] = 30) {
				corners_ud_edges_depth3[index] = i;
			}


			if (moveses == total_moves / 2) {
				std::cout << "half way for " << i << "pass \n\n";
			}

		}
		std::cout << i << " pass has finished \n\n";
	}

	for (unsigned int i = 0; i != corners_ud_edges_depth3.size(); i++) {
		corners_ud_edges_depth3[i] = corners_ud_edges_depth3[i] % 3;
	}

	std::ofstream corners_ud_edges_depth3_f("corners_ud_edges_depth3.bin", std::ios::out | std::ios::binary);
	unsigned char corners_ud_edges_depth3_compressed = 0;

	for (unsigned int i = 0; i != flipslice_twist_depth3.size() / 4; i++) { //divide by 4 because 4 values per byte

		if (i < 8806772) {
			corners_ud_edges_depth3_compressed = ((corners_ud_edges_depth3[4 * i] << 6) |
				(corners_ud_edges_depth3[4 * i + 1] << 4) |
				(corners_ud_edges_depth3[4 * i + 2] << 2) |
				(corners_ud_edges_depth3[4 * i + 3]));
		}

		else {
			corners_ud_edges_depth3_compressed = ((corners_ud_edges_depth3[4 * i] << 6) |
				(corners_ud_edges_depth3[4 * i + 1] << 4) |
				(corners_ud_edges_depth3[4 * i + 2] << 2));
		}

		corners_ud_edges_depth3_f.write((char*)&(corners_ud_edges_depth3[i]), sizeof(unsigned char));
	}
	corners_ud_edges_depth3_f.close();
	std::cout << "done";
}






inline unsigned short do_phase_1_move(unsigned long long moveses,
						std::vector <unsigned short> twist_table,
						std::vector <unsigned short> flip_table,
						std::vector <unsigned short> ud_slice_phase_2_table,
						std::vector <unsigned int> flipslice_sym_classes,
						std::vector <unsigned short> flipslice_sym,
						std::vector <unsigned short> sym_twist_conversion,
						unsigned short i									) {

	unsigned int twist = 0, flip = 0, ud_slice = 0;
	unsigned short m;
	unsigned int index = 0;
	unsigned int flipslice;

	unsigned short flipslice_class = 0;
	unsigned short flipslice_symmetry;


	while (moveses != 0) {
		unsigned short m = moveses % 18;
		moveses = moveses / 18;

		twist = twist_table[18 * twist + m];
		flip = flip_table[18 * flip + m];
		ud_slice = ud_slice_phase_2_table[432 * ud_slice + m] / 24;

		flipslice = (ud_slice << 11) + flip;

		flipslice_class = flipslice_sym_classes[flipslice];
		flipslice_symmetry = flipslice_sym[flipslice];

		twist = sym_twist_conversion[(twist << 4) + flipslice_symmetry];
		////<<4 does times 2^4 or times 16

		index = 2187 * flipslice_class + twist;

		if (flipslice_twist_depth3[index] < i) { //if it's less than it's already filled
			return 4000000000;
		}
	}

	return index;
}



void make_phase_1_pruning_table(){

	cubie c;
	std::vector <unsigned short> flipslice_sym{};
	
	for (unsigned int i = 0; i != 64430; i++) {
		flipslice_sym.push_back(0);
	}

	unsigned int index;

	std::array <cubie, 48> symmetries = gen_symmetries();
	std::array <cubie, 48> inv_symmetries = gen_inv_symmetries(symmetries);
	cubie sy;


	for (unsigned long i = 0; i != (64430 * 2187); i++) {
		flipslice_twist_depth3.push_back(30);
	}

        //All the files needed for this function


		// -------------------------------------------------------------------------------------
        
		std::ifstream twist_table_f;
        twist_table_f.open("twist move table.bin");

        std::vector <unsigned short> twist_table;

        for (unsigned int i = 0; i != 2048 * 495; i++) {
            twist_table.push_back(0);
        }

		for (unsigned int i = 0; i != 2048 * 495; i++) {
            twist_table_f.read((char*)&twist_table[i], sizeof(unsigned short));
		}

        twist_table_f.close();

		// -------------------------------------------------------------------------------------

		std::ifstream sym_twist_conversion_f;
		sym_twist_conversion_f.open("twist sym table.bin");

		std::vector <unsigned short> sym_twist_conversion;

		for (unsigned int i = 0; i != 2048 * 495; i++) {
			sym_twist_conversion.push_back(0);
		}

		for (unsigned int i = 0; i != 2048 * 495; i++) {
			sym_twist_conversion_f.read((char*)&sym_twist_conversion[i], sizeof(unsigned short));
		}

		sym_twist_conversion_f.close();

        // -------------------------------------------------------------------------------------

        std::ifstream flip_table_f;
        flip_table_f.open("flip move table.bin");

        std::vector <unsigned short> flip_table;

        for (unsigned int i = 0; i != 2048 * 495; i++) {
            flip_table.push_back(0);
        }

		for (unsigned int i = 0; i != 2048 * 495; i++) {
			flip_table_f.read((char*)&flip_table[i], sizeof(unsigned short));
		}

        flip_table_f.close();

        // -------------------------------------------------------------------------------------

        std::ifstream ud_slice_table_f;
        ud_slice_table_f.open("ud slice phase 2 move table.bin");

		std::vector <unsigned short> ud_slice_phase_2_table;

		for (unsigned int i = 0; i != 2048 * 495; i++) {
			ud_slice_phase_2_table.push_back(0);
		}

		for (unsigned int i = 0; i != 2048 * 495; i++) {
			ud_slice_table_f.read((char*)&ud_slice_phase_2_table[i], sizeof(unsigned int));
		}

		ud_slice_table_f.close();

        // -------------------------------------------------------------------------------------

        std::ifstream flipslice_sym_class_f;
        flipslice_sym_class_f.open("flipslice sym class table.bin");

        std::vector <unsigned int> flipslice_sym_classes;

        for (unsigned int i = 0; i != 2048 * 495; i++) {
            flipslice_sym_classes.push_back(0);
		}
		
		for (unsigned int i = 0; i != 2048 * 495; i++) {
			flipslice_sym_class_f.read((char*)&flipslice_sym_classes[i], sizeof(unsigned int));
		}

        flipslice_sym_class_f.close();

        // -------------------------------------------------------------------------------------

        std::ifstream flipslice_sym_rep_f;
        flipslice_sym_rep_f.open("flipslice sym rep table.bin");

        std::vector <unsigned short> flipslice_sym_rep;

        for (unsigned int i = 0; i != 64430; i++) {
            flipslice_sym_rep.push_back(0);
        }

		for (unsigned int i = 0; i != 64430; i++) {
			flipslice_sym_rep_f.read((char*)&flipslice_sym_rep[i], sizeof(unsigned short));
		}

        flipslice_sym_rep_f.close();

        // -------------------------------------------------------------------------------------

        std::ifstream flipslice_symmetry_f;
        flipslice_symmetry_f.open("flipslice symmetry table.bin");

        std::vector <unsigned short> flipslice_symmetry;

        for (unsigned int i = 0; i != 2048 * 495; i++) {
            flipslice_symmetry.push_back(0);
        }

		for (unsigned int i = 0; i != 2048 * 495; i++) {
			flipslice_sym_rep_f.read((char*)&flipslice_symmetry[i], sizeof(unsigned short));
		}

        flipslice_symmetry_f.close();


        // -------------------------------------------------------------------------------------
    
				
		unsigned long long total_moves;
		total_moves = 0;


		flipslice_twist_depth3[0] = 0;

		for (unsigned short i = 17; i != 29; i++) {
			total_moves = i * total_moves + 17;

			for (unsigned long long moveses = 0; moveses != total_moves; moveses++) {
				index = do_phase_1_move(moveses, twist_table, flip_table, ud_slice_phase_2_table, 
					flipslice_sym_classes, flipslice_sym, sym_twist_conversion, i - 16);
				
				if (index == 4000000000) {
					continue;
				}
				
				else if (flipslice_twist_depth3[index] = 30) {
					flipslice_twist_depth3[index] = i - 16;
				}


				if (moveses == total_moves / 2) {
					std::cout << "half way for " << i - 16 << " pass \n";
					std::cout << getTime() << "\n\n";
				}

				else if (i > 21 && moveses % 1024 == 1){
					std::cout << "moveses is " << moveses << "\n";
					std::cout << getTime() << "\n\n";
				}

			}
			std::cout << i - 16 << " pass has finished \n";
			std::cout << getTime() << "\n\n";
		}

		for (unsigned int i = 0; i != flipslice_twist_depth3.size(); i++) {
			flipslice_twist_depth3[i] = flipslice_twist_depth3[i] % 3;
		}

		std::ofstream flipslice_twist_depth3_f("flipslice_twist_depth3.bin", std::ios::out | std::ios::binary);
		unsigned char flipslice_twist_depth3_compressed = 0;

		for (unsigned int i = 0; i != flipslice_twist_depth3.size() / 4; i++) { //divide by 4 because 4 values per byte
			
			if (i < 140908408) { //last integer multiple of 4 before 2187 * 64430
				flipslice_twist_depth3_compressed = ((flipslice_twist_depth3[4 * i] << 6) |
													(flipslice_twist_depth3[4 * i + 1] << 4) |
													(flipslice_twist_depth3[4 * i + 2] << 2) |
													(flipslice_twist_depth3[4 * i + 3]));
			}

			else {
				flipslice_twist_depth3_compressed = ((flipslice_twist_depth3[4 * i] << 6) |
													(flipslice_twist_depth3[4 * i + 1] << 4));
			}

			flipslice_twist_depth3_f.write((char*)&(flipslice_twist_depth3[i]), sizeof(unsigned char));
		}
		flipslice_twist_depth3_f.close();
		std::cout << "done";
}
		// -------------------------------------------------------------------------------------

		////for (unsigned short i = 0; i != 64430; i++) {
		////	rep = flipslice_sym_rep[i];

		////	flip = rep % 2187;
		////	ud_slice = rep / 2187;

		////	c.set_ud_slice_phase_1(ud_slice);
		////	c.set_flip(flip);

		////	for (short s = 0; s != 16; s++) {
		////		sy = symmetries[s];
		////		sy.edge_multiply(c);
		////		sy.multiply(inv_symmetries[s]);
		////		if (c.get_ud_slice_phase_1() == ud_slice && c.get_flip() == flip) {
		////			flipslice_sym[i] |= 1 << s; //This is essentially the same as setting
		////			// to 2^s
		////		}
		////	}
		////}

		////flipslice_classes = 0;
		////twist = 0;

		////set_flipslice_twist_depth3(2187 * flipslice_classes + twist, 0);

		////done = 1;
		////depth = 0;
		////backsearch = false;

		////while (done != 64430 * 2187) {

		////	std::cout << done;

		////	depth = depth % 3;

		////	if (depth == 9) { backsearch = true; }
		////	if (depth < 8) { mult = 5; }
		////	else { mult = 1; }

		////	index = 0;

		////	for (unsigned int flipslice_class = flipslice_classes; flipslice_class != 64430; flipslice_class++) {
		////		twist = 0;
		////		while (twist < 2187) {
		////			if (backsearch == false
		////				&& index % 16 == 0
		////				&& flipslice_twist_depth3[index % 16] == 0xffffffff
		////				&& twist < 2187 - 16) {
		////				twist += 16;
		////				index += 16;
		////				continue;
		////			}

		////			if (backsearch == true) { match = (get_flipslice_twist_depth_3(index) == 3); }
		////			else { match = (get_flipslice_twist_depth_3(index) == depth % 3); }

		////			if (match == true) {
		////				flipslice = flipslice_sym_rep[flipslice_class];
		////				flip = flipslice % 2048;
		////				ud_slice = flipslice >> 11; //This is the same as div 2048 but faster


		////				for (unsigned short m = 0; m != 18; m++) {

		////					twist_new = twist_table[18 * twist + m];
		////					flip_new = flip_table[18 * flip + m];
		////					ud_slice_new = ud_slice_phase_2_table[432 * ud_slice + m] / 24;

		////					flipslice_new = (ud_slice_new << 11) + flip_new;

		////					flipslice_class_new = flipslice_sym_classes[flipslice_new];
		////					flipslice_symmetry_new = flipslice_symmetry[flipslice_new];

		////					twist_new = sym_twist_conversion[(twist << 4) + flipslice_symmetry_new];


		////					index = 2187 * flipslice_class_new + twist_new;

		////					if (backsearch == false) {
		////						if (get_flipslice_twist_depth_3(index) == 3) {
		////							set_flipslice_twist_depth3(index, (depth + 1) % 3);
		////							done++;


		////							//Everything below is just for dealing with symmetries
		////							sym = flipslice_sym[flipslice_class_new];
		////							if (sym != 1) { //Earlier the symmetries were declared using left shifts, 
		////											//here right shifts are used
		////											//if it's equal to one you can't right shift

		////								for (short i = 1; i != 16; i++) {
		////									sym >>= 1;
		////									if (sym % 2 == 1) {
		////										twist_newer = sym_twist_conversion[(twist_new << 4) + i];

		////										index_newer = 2187 * flipslice_class_new + twist_new;
		////										if (get_flipslice_twist_depth_3(index_new) == 3) {
		////											set_flipslice_twist_depth3(index_new, (depth + 1) % 3);
		////											done++;
		////										}
		////									}
		////								}

		////							}
		////						}
		////					}
		////					else {
		////						if (get_flipslice_twist_depth_3(index) == depth % 3) {
		////							set_flipslice_twist_depth3(index, (depth + 1) % 3);
		////							done++;
		////							break;
		////						}
		////					}

		////				}

		////			}
		////			twist++;
		////			index++;
		////		}
		////	}
		////	depth++;
		////}
