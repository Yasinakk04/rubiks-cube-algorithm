#pragma once
#include <iostream>

#include "turns.h"
#include "cubie.h"
#include "enums.h"
#include "moves.h"

void cubie::put_edge_in_D_face(short edge) {
	std::array <cubie, 18> moves = make_moves();
	short count = 0;

	if (edge_in_D_face(edge) == false) {

		if (edge_in_R_face(edge) == true) {
			while (edge_in_D_face(edge) == false) {
				doR(1);
				count++;
			}					
			doD(1);
			doR(4 - count);
		}

		else if (edge_in_F_face(edge) == true) {
			while (edge_in_D_face(edge) == false) {
				doF(1);
				count++;
			}

			doD(1);
			doF(4 - count);
		}

		else if (edge_in_L_face(edge) == true) {
			while (edge_in_D_face(edge) == false) {
				doL(1);
				count++;
			}

			doD(1);
			doL(4 - count);
		}

		else if (edge_in_B_face(edge) == true) {
			while (edge_in_D_face(edge) == false) {
				doB(1);
				count++;
			}

			doD(1);
			doB(4 - count); //This places what was in the UB space back in 
										//case it was a U edge
		}
	}
}

void cubie::put_U_corner_in_DBR(short corner ){
	if (corner_in_U_face(corner) == true) {
		if (corner_in_F_face(corner) == true) {
			doF(1);
			if (corner_in_D_face(corner) == true) {
				doD(1);
				doF(3);
				doD(3);
			}
			else {
				doF(2);
				doD(1);
				doF(1);
				doD(1);
			}

			//This places the corneris DFR
		}

		else { //If the corner is in the B face
			doB(1);
			if (corner_in_D_face(corner) == true) {
				doD(1);
				doB(3);
				doD(3);
			}
			else {
				doB(2);
				doD(2);
				doB(1);
				doD(1);
			}
		}
	}

	else {
		while (find_corner_pos(corner) != DFR) {
			doD(1);
		}
	}
		//This guarantees the corner to be in DFR
}

void cubie::check_U_edge_in_pos(short e_pos){
	std::array <cubie, 18> moves = make_moves();

	while (find_edge_pos(UR) == e_pos || 
		find_edge_pos(UL) == e_pos || 
		find_edge_pos(UB) == e_pos || 
		find_edge_pos(UF) == e_pos ) {
		doU(1);
	}
}

void cubie::put_U_edge_in_U_face(short edge){		//this function enumerates the cases for what moves should be done  
	std::array <cubie, 18> moves = make_moves();	//place the edge in the space and also correct its orientation

	if (edge_in_U_face(edge) == false || find_edge_ori(edge) == 1) {		
		put_edge_in_D_face(edge);


		if (find_edge_ori(edge) == 0) {
			if (edge_in_F_face(edge) == true) {	
				check_U_edge_in_pos(UF);
				doF(2);
			}

			else if (edge_in_R_face(edge) == true) {
				check_U_edge_in_pos(UR);
				doR(2);
			}

			else if (edge_in_L_face(edge) == true) {
				check_U_edge_in_pos(UL);
				doL(2);
			}

			else if (edge_in_B_face(edge) == true) {
				check_U_edge_in_pos(UB);
				doB(2);
			}
		}


		else { //if the orienation is 1
			

			check_U_edge_in_pos(UL);

			if (edge_in_F_face(edge) == true) {
				doF(1);
				doL(3);
				doF(3);
			}

			else if (edge_in_R_face(edge) == true) {
				doD(3);
				doF(1);
				doL(3);
				doF(3);
			}

			else if (edge_in_B_face(edge) == true) {
				doD(1);
				doL(3);
				doF(3);
				doD(3);
				doF(1);
				doL(2);			
			}

			else if (edge_in_L_face(edge) == true) {
				doD(1);
				doF(1);
				doL(3);
				doF(3);
			}
		}

	}
}

void cubie::put_U_corner_in_U_face(short corner) {
	while (find_corner_pos(corner) != DFR) {
		doD(1);
	}

	while (edge_perm[0] != corner) {
		doU(1);
	}

	while (find_corner_ori(corner) != 1) {
		doR(3);
		doD(1);
		doR(1);
		doD(2);
	}

	doD(3);
	doR(3);
	doD(1);
	doR(1);
	//This places the corner in URF
	//But correct with respect to the other U edges
} 
