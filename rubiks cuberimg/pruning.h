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
std::vector <unsigned char> corners_ud_edges_depth3{};

std::vector <unsigned short> fs_sym{};

std::string getTime() {
	time_t result = time(0);

	char str[26];
	ctime_s(str, sizeof str, &result);  

	return str;
}

inline unsigned short do_phase_2_move(unsigned long long moveses,
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

	unsigned short modding = 9 + i;

	unsigned short last = 25;


	for (short x = 0; x != i; x++) {
		unsigned short m = moveses % modding;

		if		(m == 3) { m = R + 1; }
		else if (m == 4) { m = F + 1; }
		else if (m == 5) { m = D; }
		else if (m == 6) { m = D + 1; }
		else if (m == 7) { m = D + 2; }
		else if (m == 8) { m = L + 1; }
		else if (m == 9) { m = B + 1; }
 
		moveses = moveses / modding;

		ud_edges = ud_edges_table[18 * ud_edges + m];
		corner = corners_table[18 * corner + m];
		corner_sym_class = corner_sym_classes[corner];
		corner_sym = corner_symmetry[corner];

		ud_edges = ud_edge_sym_conversion[(ud_edges << 4) + corner_sym];
		////<< 4 does times 2^4 or times 16

		index = 40320 * corner_sym_class + ud_edges;

		if (last = m / 3 || (corners_ud_edges_depth3[index] != x && x < i - 1)) {
			return 4000000000;										//This checks that the new mapping is one more than the last
		}																//otherwise itll mean that it's already filled in

		else if (corners_ud_edges_depth3[index] != 30) { //if it's not 3 then it's already filled									
			return 4000000000;											//this check should only happen on the last move
		}


		last = m / 3;
		modding++;
	}

	return index;
}

void make_phase_2_pruning_table() {

	for (unsigned long i = 0; i != 2768 * 40320; i++) {
		corners_ud_edges_depth3.push_back(30);
	}

	unsigned int index;

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

	for (unsigned int i = 0; i != 2769; i++) {
		corner_sym_rep.push_back(0);
	}

	for (unsigned int i = 0; i != 2769; i++) {
		corner_sym_rep_table_f.read((char*)&corner_sym_rep[i], sizeof(unsigned short));
	}

	corner_sym_rep_table_f.close();

	// -------------------------------------------------------------------------------------

	std::ifstream corner_symmetry_f;
	corner_symmetry_f.open("corner symmetry table.bin");

	std::vector <unsigned short> corner_symmetry;

	for (unsigned int i = 0; i != 40320; i++) {
		corner_symmetry.push_back(0);
	}

	for (unsigned int i = 0; i != 40320; i++) {
		corner_symmetry_f.read((char*)&corner_symmetry[i], sizeof(unsigned short));
	}

	corner_symmetry_f.close();


	// -------------------------------------------------------------------------------------


	unsigned long long total_moves = 0;


	corners_ud_edges_depth3[0] = 0;

	unsigned short pass;
	std::cout << "enter the pass to do: ";
	std::cin >> pass;

	unsigned char corners_ud_edges_depth18;

	if (pass != 1) {
		std::ifstream corners_ud_edges_depth18_fr("corners_ud_edges_depth18.bin", std::ios::in | std::ios::binary);
		for (unsigned int i = 0; i != corners_ud_edges_depth3.size() / 4; i++) { //divide by 4 because 4 values per byte

			corners_ud_edges_depth18_fr.read((char*)&corners_ud_edges_depth18, sizeof(unsigned char));
			corners_ud_edges_depth3[i] = corners_ud_edges_depth18;

		}
		corners_ud_edges_depth18_fr.close();
	}

	
	while (pass != 19) {


		for (unsigned short i = 10; i != pass + 10; i++) {
			total_moves = i * total_moves + 10;
		}
		
		if (pass != 18) {

			for (unsigned long long moveses = 0; moveses != total_moves; moveses++) {
				index = do_phase_2_move(moveses, ud_edges_table, corners_table,
					corner_sym_classes, corner_symmetry, ud_edge_sym_conversion, pass);
				if (moveses == total_moves / 2) {
					std::cout << "half way for " << pass << " pass \n";
					std::cout << getTime() << "\n\n";
				}

				else if (pass >  5 && moveses % 262144 == 1) {
					std::cout << "moveses is " << moveses << " out of " << total_moves << " and on pass " << pass << "\n";
					std::cout << getTime() << "\n\n";
				}
				if (index == 4000000000) {
					continue;
				}
				else if (corners_ud_edges_depth3[index] == 30) {
					corners_ud_edges_depth3[index] = pass;
				}



			}
			std::cout << pass << " pass has finished \n";
			std::cout << getTime() << "\n\n";
		}

		else {
			for (unsigned int i = 0; i != corners_ud_edges_depth3.size(); i++) {
				if (corners_ud_edges_depth3[i] == 30) {
					corners_ud_edges_depth3[i] = pass; //18 mod 3
				}
			}
		}

		std::ofstream corners_ud_edges_depth3_f("corners_ud_edges_depth3.bin", std::ios::out | std::ios::binary);
		unsigned char corners_ud_edges_depth3_compressed = 0;

		if (pass == 18) {
			for (unsigned int i = 0; i != flipslice_twist_depth3.size() / 4; i++) { //divide by 4 because 4 values per byte

				corners_ud_edges_depth3_compressed = ((corners_ud_edges_depth3[4 * i] << 6) |
					(corners_ud_edges_depth3[4 * i + 1] << 4) |
					(corners_ud_edges_depth3[4 * i + 2] << 2) |
					(corners_ud_edges_depth3[4 * i + 3]));

				corners_ud_edges_depth3_f.write((char*)&(corners_ud_edges_depth3_compressed), sizeof(unsigned char));
			}
			corners_ud_edges_depth3_f.close();
		}

		else {
			std::ofstream corners_ud_edges_depth18_fr("corners_ud_edges_depth18.bin", std::ios::out | std::ios::binary);
			for (unsigned int i = 0; i != corners_ud_edges_depth3.size(); i++) { //divide by 4 because 4 values per byte
				corners_ud_edges_depth18_fr.write((char*)&corners_ud_edges_depth3[i], sizeof(unsigned char));
			}
			corners_ud_edges_depth18_fr.close();
		}
		pass++;
	}

	std::cout << "done";
}






inline unsigned short do_phase_1_move(unsigned long long moveses,
						std::vector <unsigned short> twist_table,
						std::vector <unsigned short> flip_table,
						std::vector <unsigned short> ud_slice_phase_2_table,
						std::vector <unsigned int> flipslice_sym_classes,
						std::vector <unsigned short> flipslice_sym,
						std::vector <unsigned short> flipslice_rep,
						std::vector <unsigned short> sym_twist_conversion,
						unsigned short i,
						unsigned short flipslice_class_index) {

	unsigned int twist = 0, flip = 0, ud_slice = 0;
	unsigned int index = 0;
	unsigned int flipslice;

	unsigned short flipslice_class = 0;
	unsigned short flipslice_symmetry;

	unsigned short modding = 18;
	unsigned short last = 25;

	unsigned short sym;

	unsigned int twist_new;
	unsigned int index_new;

	if (i > 8) {
		twist = flipslice_class_index % 2187;
		flipslice = flipslice_rep[flipslice_class_index / 2187];

		ud_slice = flipslice >> 11;
		flip = flipslice & 0b0000011111111111;
		i = 1;
	}

	for (short x = 0; x != i; x++) {
		unsigned short m = moveses % modding;
		moveses = moveses / modding;

		if (last = m / 3) { return 4000000000; }


		twist = twist_table[18 * twist + m];
		flip = flip_table[18 * flip + m];
		ud_slice = ud_slice_phase_2_table[432 * ud_slice + m] / 24;

		flipslice = (ud_slice << 11) + flip;

		flipslice_class = flipslice_sym_classes[flipslice];
		flipslice_symmetry = flipslice_sym[flipslice];

		twist = sym_twist_conversion[(twist << 4) + flipslice_symmetry];
		////<<4 does times 2^4 or times 16

		index = 2187 * flipslice_class + twist;
		
		if ((flipslice_twist_depth3[index] != x) && x < i - 1) {
			return 4000000000;										//This checks that the new mapping is one more than the last
		}																//otherwise itll mean that it's already filled in
						
				
		last = m / 3;
		modding++;
	}
	
	sym = fs_sym[flipslice_class];


	if (flipslice_twist_depth3[index] == 30 && i < 8) { //if it's 30 then it's not already filled									
												//this check should only happen on the last move
		flipslice_twist_depth3[index] = i;

		if (sym != 1) {
			for (unsigned short j = 0; j != 16; j++) {
				sym >>= 1;

				if (sym % 2 == 1) {
					twist_new = sym_twist_conversion[(twist << 4) + j];
					index_new = 2187 * flipslice_class + twist_new;

					if (flipslice_twist_depth3[index_new] == 30) {
						flipslice_twist_depth3[index] = i;
					}
				}
			}
		}
	}

	else if (flipslice_twist_depth3[index] != 30) {
		flipslice_twist_depth3[flipslice_class_index] = flipslice_twist_depth3[index] + modding - 18;
	}

	return 0;
}



void make_phase_1_pruning_table(){
	std::vector <unsigned short> flipslice_sym{};

	unsigned int index;

	std::array <cubie, 48> symmetries = gen_symmetries();
	std::array <cubie, 48> inv_symmetries = gen_inv_symmetries(symmetries);
	cubie cc;
	cubie sy;
	
	std::cout << "okokofk";

	for (unsigned int i = 0; i != 64430; i++) {
		flipslice_sym.push_back(0);

		cc.set_ud_slice_phase_2(i / 2048);
		cc.set_flip(i % 2048);

		fs_sym.push_back(0);

		for (unsigned char x = 0; x != 16; x++) {
			sy = symmetries[x];
			unsigned short y = 0x0000000000000000;

			sy.edge_multiply(cc);
			sy.edge_multiply(inv_symmetries[x]);

			if (sy.get_ud_slice_phase_2() == i / 2048 && sy.get_flip() == i % 2048) {
				y |= 1 << x;
			}
			fs_sym.push_back(y);
		}
	}

	for (unsigned long i = 0; i != (64430 * 2187); i++) {
		flipslice_twist_depth3.push_back(30);
	}

       //All the files needed for this function


	// -------------------------------------------------------------------------------------
       
	std::ifstream twist_table_f;
       twist_table_f.open("twist move table.bin");

       std::vector <unsigned short> twist_table;

       for (unsigned int i = 0; i != 2187 * 18; i++) {
           twist_table.push_back(0);
       }

	for (unsigned int i = 0; i != 2187 * 18; i++) {
           twist_table_f.read((char*)&twist_table[i], sizeof(unsigned short));
	}

       twist_table_f.close();

	// -------------------------------------------------------------------------------------

	std::ifstream sym_twist_conversion_f;
	sym_twist_conversion_f.open("twist sym table.bin");

	std::vector <unsigned short> sym_twist_conversion;

	for (unsigned int i = 0; i != 2187 * 16; i++) {
		sym_twist_conversion.push_back(0);
	}

	for (unsigned int i = 0; i != 2187 * 16; i++) {
		sym_twist_conversion_f.read((char*)&sym_twist_conversion[i], sizeof(unsigned short));
	}

	sym_twist_conversion_f.close();

       // -------------------------------------------------------------------------------------

       std::ifstream flip_table_f;
       flip_table_f.open("flip move table.bin");

       std::vector <unsigned short> flip_table;

       for (unsigned int i = 0; i != 2048 * 18; i++) {
           flip_table.push_back(0);
       }

	for (unsigned int i = 0; i != 2048 * 18; i++) {
		flip_table_f.read((char*)&flip_table[i], sizeof(unsigned short));
	}

       flip_table_f.close();

       // -------------------------------------------------------------------------------------

       std::ifstream ud_slice_table_f;
       ud_slice_table_f.open("ud slice phase 2 move table.bin");

	std::vector <unsigned short> ud_slice_phase_2_table;

	for (unsigned int i = 0; i != 11880 * 18; i++) {
		ud_slice_phase_2_table.push_back(0);
	}

	for (unsigned int i = 0; i != 11880 * 18; i++) {
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

	unsigned short pass;
	std::cout << "enter the pass to do: ";

	std::cin >> pass;
	
	if (pass != 1) {
		unsigned char flipslice_twist_depth18 = 0;
		
		std::ifstream flipslice_twist_depth18_fr("flipslice_twist_depth18.bin", std::ios::in | std::ios::binary);
		for (unsigned int i = 0; i != flipslice_twist_depth3.size(); i++) { //divide by 4 because 4 values per byte
		
			flipslice_twist_depth18_fr.read((char*)&flipslice_twist_depth18, sizeof(unsigned char));		
			flipslice_twist_depth3[i] = flipslice_twist_depth18;
		}
		flipslice_twist_depth18_fr.close();
	}

	while (pass != 13) {
		if (pass < 8) {

			for (unsigned short i = 17; i != pass + 17; i++) {
				total_moves = i * total_moves + 17;
			}

			for (unsigned long long moveses = 0; moveses != total_moves; moveses++) {
				index = do_phase_1_move(moveses, twist_table, flip_table, ud_slice_phase_2_table,
					flipslice_sym_classes, flipslice_sym, sym_twist_conversion, flipslice_sym_rep, pass, 0);

				if (moveses == total_moves / 2) {
					std::cout << "half way for " << pass << " pass \n";
					std::cout << getTime() << "\n\n";
				}

				else if (pass >= 5 && moveses % 262144 == 1) {
					std::cout << "moveses is " << moveses << " out of " << total_moves << " and pass is " << pass << "\n";
					std::cout << getTime() << "\n\n";
				}
			}
			std::cout << pass << " pass has finished \n";
			std::cout << getTime() << "\n\n";
		}

		else if (pass < 12) {
			for (unsigned int i = 0; i != sizeof(flipslice_twist_depth3); i++) {
				if (flipslice_twist_depth3[i] == 30) {
					for (unsigned long long moveses = 0; moveses != 18; moveses++) {
						do_phase_1_move(moveses, twist_table, flip_table, ud_slice_phase_2_table,
							flipslice_sym_classes, flipslice_sym, sym_twist_conversion, flipslice_sym_rep, pass, i);
					}
				}
			}
		}



		if (pass == 12) {
			for (unsigned int i = 0; i != flipslice_twist_depth3.size(); i++) {
				if (flipslice_twist_depth3[i] == 30) {
					flipslice_twist_depth3[i] = pass;
				}
			}

			std::ofstream flipslice_twist_depth3_f("flipslice_twist_depth3.bin", std::ios::out | std::ios::binary);
			for (unsigned int i = 0; i != flipslice_twist_depth3.size() / 4; i++) { //divide by 4 because 4 values per byte

				unsigned char flipslice_twist_depth3_compressed = 0;

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

				flipslice_twist_depth3_f.write((char*)&flipslice_twist_depth3_compressed, sizeof(unsigned char));
			}
			flipslice_twist_depth3_f.close();
		}

		else {
			std::ofstream flipslice_twist_depth18_fr("flipslice_twist_depth18.bin", std::ios::out | std::ios::binary);
			for (unsigned int i = 0; i != flipslice_twist_depth3.size(); i++) { //divide by 4 because 4 values per byte
				flipslice_twist_depth18_fr.write((char*)&flipslice_twist_depth3[i], sizeof(unsigned char));
			}
			flipslice_twist_depth18_fr.close();
			
		}
		pass++;
	}
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
