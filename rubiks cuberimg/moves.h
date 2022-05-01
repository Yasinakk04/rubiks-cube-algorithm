#pragma once

#include <array>
#include <iostream>
#include <fstream>
#include <vector>

#include "enums.h"
#include "cubie.h"

cubie U_turn({ UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB },		//these define the cubes for each of the 6 turns
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

cubie R_turn({ DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR },
		{ 2, 0, 0, 1, 1, 0, 0, 2 },
		{ FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

cubie F_turn({ UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB },
		{ 1, 2, 0, 0, 2, 1, 0, 0 },
		{ UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR },
		{ 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0 });

cubie D_turn({ URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

cubie L_turn({ URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB },
		{ 0, 1, 2, 0, 0, 2, 1, 0 },
		{ UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

cubie B_turn({ URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL },
		{ 0, 0, 1, 2, 0, 0, 2, 1 },
		{ UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 });

std::array <cubie, 18> make_moves() {
	std::array <cubie, 18> moves;
	moves[0] = U_turn;
	moves[3] = R_turn;
	moves[6] = F_turn;
	moves[9] = D_turn;
	moves[12] = L_turn;
	moves[15] = B_turn;

	for (short m = 0; m != 18; m++) {

		if (m % 3 == 0) {
			continue;
		}
		//indexes that are multiples of 3 have already been filled in

		short times = m % 3;
		//The integer result of m mod 3 is the number of moves - 1
		//for instance 15 mod 3 is 0, so it's applied once

		moves[m] = moves[m - (m % 3)];

		while (times != 0) {
			moves[m].multiply(moves[m - (m % 3)]);
			times--;
		}
	}


	return moves;
}

void make_twist_table() {
	std::array <cubie, 18> moves = make_moves();
	std::vector <unsigned short> twist_table;

	for (int i = 0; i != 2187 * 18; i++) {
		twist_table.push_back(0);
	}

	cubie c;

	for (unsigned short t = 0; t != 2187; t++) { //This for loop enumerates through every corner permutation
		for (unsigned short i = 0; i != 18; i++) { //this one then enumerates through every move
			c.set_twist(t);
			c.corner_multiply(moves[i]);
			twist_table[18 * t + i] = c.get_twist(); //With the table produced, you can work out the permutation
		}												//of the new cube by inputting into this array the
													   //last permutation value, t, and the move, i
	}

	std::ofstream something("twist move table.bin", std::ios::out | std::ios::binary);

	for (int i = 0; i != 2187 * 18; i++) {
		something.write((char*)&(twist_table[i]), sizeof(unsigned short));
	}

	something.close();
}

void make_flip_table() {
	std::array <cubie, 18> moves = make_moves();
	std::vector <unsigned short> flip_table;

	for (int i = 0; i != 2048 * 18; i++) {
		flip_table.push_back(0);
	}

	cubie c;

	for (short f = 0; f != 2048; f++) { //This works essentially the same as the twist table
		for (short i = 0; i != 18; i++) { //the only difference is that the table has to be a different size
			c.set_flip(f); //and edge multiplication happens rather than corner multiplication
			c.edge_multiply(moves[i]);
			flip_table[18 * f + i] = c.get_flip();
		}
	}

	std::ofstream something("flip move table.bin", std::ios::out | std::ios::binary);

	for (int i = 0; i != 2048 * 18; i++) {
		something.write((char*)&(flip_table[i]), sizeof(unsigned short));
	}

	something.close();
}

void make_ud_edges_table() {
	std::array <cubie, 18> moves = make_moves();

	std::vector <unsigned short> ud_edges_table;

	for (int i = 0; i != 40320 * 18; i++) {
		ud_edges_table.push_back(0);
	}

	cubie c;

	for (unsigned short ud = 0; ud != 40320; ud++) {
		for (short i = 0; i != 18; i++) {
			c.set_ud_edges(ud);
			c.edge_multiply(moves[i]);
			ud_edges_table[18 * ud + i] = c.get_ud_edges();
		}
	}

	std::ofstream something("ud edges move table.bin", std::ios::out | std::ios::binary);

	for (int i = 0; i != 40320 * 18; i++) {
		something.write((char*)&(ud_edges_table[i]), sizeof(unsigned short));
	}
	something.close();
}

void make_corners_table() {

	std::array <cubie, 18> moves = make_moves();
	std::vector <unsigned short> corners_table;

	for (unsigned int i = 0; i != 40320 * 18; i++) {
		corners_table.push_back(0);
	}

	cubie c;

	for (unsigned short corn = 0; corn != 40320; corn++) {
		for (short i = 0; i != 18; i++) {
			c.set_corners(corn);
			c.corner_multiply(moves[i]);
			corners_table[18 * corn + i] = c.get_corners();
		}
	}

	std::ofstream something("corners move table.bin", std::ios::out | std::ios::binary);

	for (int i = 0; i != 40320 * 18; i++) {
		something.write((char*)&(corners_table[i]), 2);
	}

	something.close();
}

void make_ud_slice_phase_2_table() {

	std::array <cubie, 18> moves = make_moves();
	std::vector <unsigned short> ud_slice_phase_2_table;

	for (unsigned int i = 0; i != 11880 * 18; i++) {
		ud_slice_phase_2_table.push_back(0);
	}

	cubie c;

	for (unsigned short ud = 0; ud != 11880; ud++) {
		for (short i = 0; i != 18; i++) {
			c.set_ud_slice_phase_2(ud);
			c.edge_multiply(moves[i]);
			ud_slice_phase_2_table[18 * ud + i] = c.get_ud_slice_phase_2();
		}
	}

	std::ofstream something("ud slice phase 2 move table.bin", std::ios::out | std::ios::binary);

	for (int i = 0; i != 11880 * 18; i++) {
		something.write((char*)&(ud_slice_phase_2_table[i]), 2);
	}
	something.close();
}