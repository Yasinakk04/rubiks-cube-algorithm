#pragma once
#include "cubie.h"
#include "enums.h"
#include "moves.h"

void cubie::put_edge_in_D_face(unsigned short edge) {
	std::array <cubie, 18> moves = make_moves();

	if (edge_in_R_face(edge) == true) {
		do {
			multiply(moves[3 * R]);
		} while (edge_in_D_face(edge) == false);	//for do while loop
													//https://www.w3schools.com/cpp/cpp_do_while_loop.asp					
		multiply(moves[3 * D]);
		multiply(moves[3 * R + 2]);						
	}												

	else if (edge_in_F_face(edge) == true) {
		do {
			multiply(moves[3 * F]);
		} while (edge_in_D_face(edge) == false);

		multiply(moves[3 * D]);
		multiply(moves[3 * F + 2]);
	}

	else if (edge_in_L_face(edge) == true) {
		do {
			multiply(moves[3 * L]);
		} while (edge_in_D_face(edge) == false);

		multiply(moves[3 * D]);
		multiply(moves[3 * L + 2]);
	}

	else if (edge_in_B_face(edge) == true) {
		do {
			multiply(moves[3 * B]);
		} while (edge_in_D_face(edge) == false);

		multiply(moves[3 * D]);
		multiply(moves[3 * B + 2]); //This places what was in the UB space back in 
									//case it was a U edge
	}
}

void cubie::check_U_edge_in_pos(unsigned short e_pos){
	std::array <cubie, 18> moves = make_moves();

	while (find_edge_pos(UR) == e_pos || 
		find_edge_pos(UL) == e_pos || 
		find_edge_pos(UB) == e_pos || 
		find_edge_pos(UF) == e_pos ) {
		multiply(moves[U * 3]);
	}
}

inline void cubie::put_U_edge_in_U_face(unsigned short edge){
	std::array <cubie, 18> moves = make_moves();

	if (edge_in_U_face(edge) == false || find_edge_ori(edge) == 1) {
		put_edge_in_D_face(edge);


		if (find_edge_ori(edge) == 0) {
			if (edge_in_F_face(edge) == true) {
				check_U_edge_in_pos(UF);
				multiply(moves[3 * F + 1]);
			}

			else if (edge_in_R_face(edge) == true) {
				check_U_edge_in_pos(edge);
				multiply(moves[3 * R + 1]);
			}

			else if (edge_in_L_face(edge) == true) {
				check_U_edge_in_pos(UL);
				multiply(moves[3 * L + 1]);
			}

			else if (edge_in_B_face(edge) == true) {
				check_U_edge_in_pos(UB);
				multiply(moves[3 * B + 1]);
			}
		}


		else { //if the orienation is 1

			check_U_edge_in_pos(UL);

			if (edge_in_F_face(edge) == true) {
				multiply(moves[3 * F]);
				multiply(moves[3 * L]);
			}

			else if (edge_in_R_face(edge) == true) {
				multiply(moves[3 * D + 2]);
				multiply(moves[3 * F]);
				multiply(moves[3 * L]);
				std::cout << edge << ": hello\n\n";
			}

				multiply(moves[3 * F]);
				multiply(moves[3 * L]);
			}

			else if (edge_in_B_face(edge) == true) {
			}
		}
	}
}