#pragma once

#include <array>
#include <iostream>
#include <fstream>
#include "enums.h"
#include "cubie.h"

inline cubie make_U_turn() {
	cubie U_turn;
	U_turn.set_corn_perm( { UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB });
	U_turn.set_corn_ori( { 0, 0, 0, 0, 0, 0, 0, 0 });
	U_turn.set_edge_perm( { UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR });
	U_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return U_turn;
}

inline cubie make_R_turn() {
	cubie R_turn;
	R_turn.set_corn_perm( { DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR });
	R_turn.set_corn_ori( { 2, 0, 0, 1, 1, 0, 0, 2 });
	R_turn.set_edge_perm( { FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR });
	R_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return R_turn;
}

inline cubie make_F_turn() {
	cubie F_turn;
	F_turn.set_corn_perm( { UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB });
	F_turn.set_corn_ori( { 1, 2, 0, 0, 2, 1, 0, 0 });
	F_turn.set_edge_perm( { UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR });
	F_turn.set_edge_ori( { 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0	});
	return F_turn;
}

inline cubie make_D_turn() {
	cubie D_turn;
	D_turn.set_corn_perm( { URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR });
	D_turn.set_corn_ori( { 0, 0, 0, 0, 0, 0, 0, 0 });
	D_turn.set_edge_perm( { UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR });
	D_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return D_turn;
}

inline cubie make_L_turn() {
	cubie L_turn;
	L_turn.set_corn_perm( { URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB });
	L_turn.set_corn_ori( { 0, 1, 2, 0, 0, 2, 1, 0 });
	L_turn.set_edge_perm( { UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR });
	L_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return L_turn;
}

inline cubie make_B_turn() {
	cubie B_turn;
	B_turn.set_corn_perm( { URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL });
	B_turn.set_corn_ori( { 0, 0, 1, 2, 0, 0, 2, 1 });
	B_turn.set_edge_perm( { UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB });
	B_turn.set_edge_ori( { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 });
	return B_turn;
}


inline void test() {
//	std::ofstream myfile;
//	myfile.open("something.bin", std::ios::binary | std::ios::out);
//	myfile.read()
//	myfile.close();
}

inline std::array <cubie, 18> make_moves() {
	std::array <cubie, 18> moves;
	moves[0] = make_U_turn();
	moves[1] = make_R_turn();
	moves[2] = make_F_turn();
	moves[3] = make_D_turn();
	moves[4] = make_L_turn();
	moves[5] = make_B_turn();

	for (short m = 6; m != 18; m++) {
		
		short times = m / 6;
		//The integer result of m div 6 is the number of moves -1
		//for instance 15 div 6 is 2, so it's applied 3 times

		moves[m] = moves[m % 6];
		//the move mod 6 is the actual move
		//7 mod 6 is 1, so it's R

		while (times != -1) {
			moves[m].multiply(moves[m % 6]);
			times--;
		}
	}

	return moves;
}

inline void make_twist_table() {
	std::array <cubie, 18> moves = make_moves();

	std::array <unsigned short, 2187 * 18> twist_table;

	cubie c;

	for (long t = 0; t != 2187; t++){				//This for loop enumerates through every corner permutation
		for (long i = 0; i != 18; i++) {			//this one then enumerates through every move
			c.set_twist(t);
			c.corner_multiply(moves[i]);
			twist_table[18 * t + i] = c.get_twist();		//With the table produced, you can work out the permutation
		}													//of the new cube by inputting into this array the 
															//last permutation value, t, and the move, i
		if (t == 1000) {
		std::cout << twist_table[0] << "\n\n";
		}
	}

	std::ofstream something("twist move table.txt", std::ios::out | std::ios::binary);

	for (int i = 0; i != 2187 * 18; i++) {
		twist_table[i]++;
		something << twist_table[i];
	}

	something.close();
}


//
//void make_flip_table() {
//	std::array <cubie, 18> moves = make_moves();
//
//	std::array <short, 2048 * 18> flip_table;
//
//	cubie c;
//
//	for (short f = 0; f != 2048; f++) {				//This works essentially the same as the twist table
//		for (short i = 0; i != 18; i++) {			//the only difference is that the table has to be a different size
//			c.set_flip(f);							//and edge multiplication happens rather than corner multiplication
//			c.edge_multiply(moves[i]);			
//			flip_table[18 * f + i] = c.get_flip();	
//		}						
//	}
//}
//
//void make_ud_edges_table() {
//	std::array <cubie, 18> moves = make_moves();
//
//	std::array <unsigned short, 40320 * 18> flip_table;
//	cubie c;
//
//	for (unsigned short ud = 0; ud != 40320; ud++) {
//		for (short i = 0; i != 18; i++) {			
//			c.set_ud_edges(ud);						
//			c.edge_multiply(moves[i]);
//			flip_table[18 * ud+ i] = c.get_ud_edges();
//		}
//	}
//}
//
//void make_corners_table() {
//	std::array <cubie, 18> moves = make_moves();
//
//	std::array <unsigned short, 40320 * 18> corners_table;
//	cubie c;
//
//	for (unsigned short corn = 0; corn != 40320; corn++) {
//		for (short i = 0; i != 18; i++) {
//			c.set_corners(corn);
//			c.corner_multiply(moves[i]);
//			corners_table[18 * corn + i] = c.get_corners();
//		}
//	}
//}
//
//void make_ud_slice_phase_2_table() {
//	std::array <cubie, 18> moves = make_moves();
//
//	std::array <short, 11880 * 18> ud_slice_phase_2_table;
//	cubie c;
//
//	for (short ud = 0; ud != 11880; ud++) {
//		for (short i = 0; i != 18; i++) {
//			c.set_ud_slice_phase_2(ud);
//			c.corner_multiply(moves[i]);
//			ud_slice_phase_2_table[18 * ud + i] = c.get_ud_slice_phase_2();
//		}
//	}
//}