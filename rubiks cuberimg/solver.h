#pragma once

#include <array>
#include <iostream>

#include "enums.h"

#include "facelets.h"
#include "to facelet.h"
#include "cubie.h"
#include "moves.h"
#include "place edge in right place.h"

cubie final_algorithm(cubie cube, cubie F_move, cubie L_move, cubie B_move) {
	std::vector <short> algorithm =
	{ L + 6, L + 6,
	B + 6, B + 6, 
	L + 6, L + 6, L + 6, 
	F + 6, F + 6, F + 6,
	L + 6, 
	B + 6, B + 6, 
	L + 6, L + 6, L + 6, 
	F + 6, 
	L + 6, L + 6, L + 6 };

	//L2 B2 L' F' L B2 L' F L'

	std::array<cubie, 18> moves = make_moves();

	cubie x;
	cubie y;
	cubie I;
	I.reset();

	for (short i = 0; i != 3; i++) {
		for (short m = 0; m != 6; m++) {
			x = moves[m * 3 + 2];

			if (i == 0) { y = F_move; }
			else if (i == 1) { y = L_move; }
			else { y = B_move; }

			y.multiply(x);

			if (I.compare(y) == true) {
				for (short j = 0; j != algorithm.size(); j++) {
					if (algorithm[j] == F + 6 && i == 0) {
						algorithm[j] = m;
					}

					else if (algorithm[j] == L + 6 && i == 1) {
						algorithm[j] = m;
					}

					else if (algorithm[j] == B + 6 && i == 2) {
						algorithm[j] = m;
					}
				}
				break;
			}
		}
	}

	cube.do_move_vector(algorithm);
	return cube;
}

cubie second_to_last_step_algorithm(cubie cube, cubie F_move, cubie R_move, cubie L_move) {
	std::vector <short> algorithm =
	{ R + 6, R + 6, U, U, U, R + 6, R + 6, R + 6, L + 6, F + 6, F + 6, L + 6, L + 6, 
		L + 6, R + 6, D, D, U, R + 6, R + 6 };


	std::array <cubie, 18> moves = make_moves();
	cubie x;
	cubie y;
	cubie I;
	I.reset();


	for (short i = 0; i != 3; i++) {
		
		for (short m = 0; m != 6; m++) {
			x = moves[m * 3 + 2];

			if (i == 0) { y = F_move; }
			else if (i == 1) { y = L_move; }
			else { y = R_move; }



			y.multiply(x);

			if (I.compare(y) == true) {
				for (short j = 0; j != algorithm.size(); j++) {
					if (algorithm[j] == F + 6 && i == 0) {
						algorithm[j] = m;
					}

					else if (algorithm[j] == L + 6 && i == 1) {
						algorithm[j] = m;
					}

					else if (algorithm[j] == R + 6 && i == 2) {
						algorithm[j] = m;
					}
				}
				break;
			}
		}
	}
	return cube;
}

cubie mid_layer_algorithm_R(cubie cube, cubie F_move, cubie R_move) {
	std::vector <short> algorithm =
	{ F + 6, 
	D, 
	F + 6, F + 6, F + 6, 
	D, D, D, 
	R + 6, R + 6, R + 6, 
	D, D, D, 
	R + 6 };
	//F D F' D' R' D' R
	

	std::array <cubie, 18> moves = make_moves();
	cubie x;
	cubie y;
	cubie I;
	I.reset();



	for (short i = 0; i != 2; i++) {

		for (short m = 0; m != 6; m++) {

			if (i == 0) { y = F_move; }
			else { y = R_move; }
			
			x = moves[m * 3 + 2];
			y.multiply(x);

			

			if (I.compare(y) == true) {
				for (short j = 0; j != algorithm.size(); j++) {
					if (algorithm[j] == F + 6 && i == 0) {
						algorithm[j] = m;
					}

					else if (algorithm[j] == R + 6 && i == 1) {
						algorithm[j] = m;
					}
				}
				break;
			}
		}
	}

	cube.do_move_vector(algorithm);
	return cube;
}

cubie mid_layer_algorithm_L(cubie cube, cubie F_move, cubie L_move) {
	std::vector <short> algorithm =
	{ F + 6, F + 6, F + 6, 
	D, D, D, 
	F + 6, 
	D, 
	L + 6, 
	D, 
	L + 6, L + 6, L + 6 };

	// F' D' F D L D L'

	//URFDLB
	
	std::array <cubie, 18> moves = make_moves();
	cubie x;
	cubie y;
	cubie I;
	I.reset();
		
	for (short i = 0; i != 2; i++) {
		for (short m = 0; m != 6; m++) {
			
			if (i == 0) { y = F_move; }
			else { y = L_move; }

			x = moves[m * 3 + 2];
			y.multiply(x);

			if (I.compare(y) == true) {
				for (short j = 0; j != algorithm.size(); j++) {
					if (algorithm[j] == F + 6 && i == 0) {
						algorithm[j] = m;
					}

					else if (algorithm[j] == L + 6 && i == 1) {
						algorithm[j] = m;
					}
				}
				break;
			}
		}	
	}

	cube.do_move_vector(algorithm);
	return cube;
}

cubie white_cross(cubie cube) {
		std::array <cubie, 18> moves = make_moves();

	if (cube.edge_perm[0] != 0 || cube.edge_ori[0] != 0			//This checks if there is already
		|| cube.edge_perm[1] != 1 || cube.edge_ori[1] != 0			//a white cross or not
		|| cube.edge_perm[2] != 2 || cube.edge_ori[2] != 0
		|| cube.edge_perm[3] != 3 || cube.edge_ori[3] != 0) {

		cube.put_U_edge_in_U_face(UR);
		cube.put_U_edge_in_U_face(UL);
		cube.put_U_edge_in_U_face(UF);
		cube.put_U_edge_in_U_face(UB);

		//This ensures each of the 4 edges have been placed in the U face
	}

	//Now it needs to extend the white cross to the other centres

	if (cube.edge_perm[0] != 0 ||
		cube.edge_perm[1] != 1 ||
		cube.edge_perm[2] != 2 ||
		cube.edge_perm[3] != 3) {

		while (cube.edge_perm[0] != 0) {
			cube.doU(1);
		}

		if (cube.edge_perm[1] != 1) {
			if (cube.edge_perm[3] == 1) {  //if it's opposite
				cube.doF(2);
				cube.doB(2);
				cube.doD(2);
				cube.doF(2);
				cube.doB(2);
			}

			else { //if it's adjacent
				cube.doF(2);
				cube.doL(2);
				cube.doD(1);
				cube.doF(2);
				cube.doD(2);
				cube.doL(2);
			}
		}

		cube.output_cubie();

		//At this point UF and UR are in the correct places
		//Now it need to swap UB and UL or 
		//they already are in the corrct places

		if (cube.edge_perm[3] != 3) {
			cube.doB(2);
			cube.doL(2);
			cube.doD(1);
			cube.doL(2);
			cube.doD(2);
			cube.doB(2);
		}

	}

	//white cross extended
	return cube;
}

cubie white_face(cubie cube) {
	if ((cube.corn_perm[0] != 0 || cube.corn_ori[0] != 0		//This checks that U face is done or not	
		|| cube.corn_perm[1] != 1 || cube.corn_ori[1] != 0
		|| cube.corn_perm[2] != 2 || cube.corn_ori[2] != 0
		|| cube.corn_perm[3] != 3 || cube.corn_ori[3] != 0)) {

		if (cube.corn_perm[0] != 0 || cube.corn_ori[0] != 0) {
			cube.put_U_corner_in_DBR(URF);
			cube.put_U_corner_in_U_face(URF);
		}

		if (cube.corn_perm[1] != 1 || cube.corn_ori[1] != 0) {
			cube.put_U_corner_in_DBR(UFL);
			cube.put_U_corner_in_U_face(UFL);
		}

		if (cube.corn_perm[2] != 2 || cube.corn_ori[2] != 0) {
			cube.put_U_corner_in_DBR(ULB);
			cube.put_U_corner_in_U_face(ULB);
		}

		if (cube.corn_perm[3] != 3 || cube.corn_ori[3] != 0) {
			cube.put_U_corner_in_DBR(UBR);
			cube.put_U_corner_in_U_face(UBR);
		}

		while (cube.corn_perm[0] != 0) {
			cube.doU(1);
		}

		return cube;
	}
}

cubie middle_layer(cubie cube) {
	while (cube.edge_perm[8] != 8 || cube.edge_ori[8] != 0			//This is to check if all the middle edges
		|| cube.edge_perm[9] != 9 || cube.edge_ori[9] != 0			//are in their places
		|| cube.edge_perm[10] != 10 || cube.edge_ori[10] != 0
		|| cube.edge_perm[11] != 11 || cube.edge_ori[11] != 0) {

		if (cube.edge_in_D_face(FR) == false	//This next stage requires at least one edge
			&& cube.edge_in_D_face(FL) == false //to begin in the D face
			&&	cube.edge_in_D_face(BR) == false 
			&& cube.edge_in_D_face(BL) == false) {
			cube.doF(1);
			cube.doD(1);
			cube.doF(3);
			cube.doD(3);
			cube.doR(3);
			cube.doD(3);
			cube.doR(1); //this sequence of moves will swap the edge in FR with
		}				 //DL with DF with DB back to FR

		short edge = 0;
		for (short i = DR; i <= DB; i++) {
			if (cube.edge_perm[i] >= FR) {
				edge = cube.edge_perm[i];
				break;
			}
		}

		std::array <cubie, 18> moves = make_moves();

		cubie F_move;
		cubie R_move;
		cubie L_move;

		if (cube.find_edge_ori(edge) == 0) {
			switch (edge) {
			case FR:
				while (cube.find_edge_pos(edge) != DB) { cube.doD(1); }

				F_move = moves[F * 3];
				R_move = moves[R * 3];

				cube = mid_layer_algorithm_R(cube, F_move, R_move);

				break;
			case FL:
				while (cube.find_edge_pos(edge) != DB) { cube.doD(1); }

				F_move = moves[F * 3];
				L_move = moves[L * 3];

				cube = mid_layer_algorithm_L(cube, F_move, L_move);
				break;

			case BL:
				while (cube.find_edge_pos(edge) != DF) { cube.doD(1); }

				F_move = moves[B * 3];
				R_move = moves[L * 3];

				cube = mid_layer_algorithm_R(cube, F_move, R_move);
				break;
			case BR:
				while (cube.find_edge_pos(edge) != DF) { cube.doD(1); }

				F_move = moves[B * 3];
				L_move = moves[R * 3];

				cube = mid_layer_algorithm_L(cube, F_move, L_move);
				break;
			}
		}

		else { //the orientation is 1
			switch (edge) {
			case FR:
				while (cube.find_edge_pos(edge) != DL) { cube.doD(1); }

				F_move = moves[R * 3];
				L_move = moves[F * 3];

				cube = mid_layer_algorithm_L(cube, F_move, L_move);

				break;
			case FL:
				while (cube.find_edge_pos(edge) != DR) { cube.doD(1); }

				F_move = moves[L * 3];
				R_move = moves[F * 3];

				cube = mid_layer_algorithm_R(cube, F_move, R_move);
				break;

			case BL:
				while (cube.find_edge_pos(edge) != DR) { cube.doD(1); }

				F_move = moves[L * 3];
				L_move = moves[B * 3];

				cube = mid_layer_algorithm_L(cube, F_move, L_move);
				break;
			case BR:
				while (cube.find_edge_pos(edge) != DL) { cube.doD(1); }

				F_move = moves[R * 3];
				R_move = moves[B * 3];

				cube = mid_layer_algorithm_R(cube, F_move, R_move);
				break;
			}					
		}
	}

	return cube;
}

cubie yellow_cross(cubie cube) {
	if (cube.edge_ori[4] != 0 ||	//this checks if there already 
		cube.edge_ori[B] != 0 ||	//a yellow cross
		cube.edge_ori[6] != 0 ||	
		cube.edge_ori[7] != 0) {

		for (unsigned char i = DR; i <= DB; i++) {
			if (cube.edge_ori[i] == 0) { break; }

			if (i == DB) {
				cube.doF(1);
				cube.doL(1);
				cube.doD(1);
				cube.doL(3);
				cube.doD(3);
				cube.doF(3);
				break;
			}
		}

		//Now it's guaranteed at least 2 edges are orientated 
		//of the 4 yellow faces

		//at this point all 4 edges are yellow so we only check that 
		//they're orientated
		if ((cube.edge_ori[4] == 0 && cube.edge_ori[6] == 0) || //this checks if the 
			(cube.edge_ori[B] == 0 && cube.edge_ori[7] == 0)) { //orientated faces are opposite 
																//eachother
			if (cube.edge_ori[B] == 0 && cube.edge_ori[7] == 0) {
				cube.doD(1);		//this guarantees they're placed in DR and DL
			}
			
			
			cube.doF(1);
			cube.doL(1);
			cube.doD(1);
			cube.doL(3);
			cube.doD(3);
			cube.doF(3);		
		}

		else {
			while (cube.edge_ori[4] == 1 || cube.edge_ori[7] == 1) {
				cube.doD(1);
			}

			cube.doF(1);
			cube.doD(1);
			cube.doL(1);
			cube.doD(3);
			cube.doL(3);
			cube.doF(3);
		}
	}

	return cube;
}

cubie second_to_last_step(cubie cube) {
	for (unsigned char i = 0; i != 4; i++) {
		cube.doD(1);
		if (cube.edge_perm[4] == 4 &&
			cube.edge_perm[5] == 5 &&
			cube.edge_perm[6] == 6 &&
			cube.edge_perm[7] == 7) {

			return cube;
		}
	}
	//this is to check if the edges are 
	//already in the correct order or not

	unsigned char check = 0;
	while (check != 1) {
		check = 0;
		for (unsigned char i = 0; i != 4; i++) {
			cube.doD(1);
			for (unsigned char j = DR; j <= DB; j++) {
				if (cube.edge_perm[j] == j) { 
					check++;
				}
			}

			if (check == 1) {
				break;
			}
		}

		if (check > 1) {
			cube.doR(2);
			cube.doU(3);
			cube.doR(3);
			cube.doL(1);
			cube.doB(2);
			cube.doL(3);
			cube.doR(1);
			cube.doD(2);
			cube.doU(1);
			cube.doR(2);
		}
	}

	short edge = 0;

	for (unsigned char j = DR; j <= DB; j++) {
		if (cube.edge_perm[j] == j) {
			edge = j;
			break;
		}
	}
	short next_edge = edge + 1;
	short other_edge = edge - 2;


	if (next_edge == 8) { next_edge = 4; } 
	if (other_edge < 4) { other_edge = other_edge + 4; }

	cubie F_move;
	cubie R_move;
	cubie L_move;

	std::cout << next_edge << "\n";

	std::array <cubie, 18> moves = make_moves();
	cube.output_cubie();
	
	if (cube.edge_perm[next_edge] == other_edge) {
		switch (next_edge) {
		case DR:
			F_move = moves[R * 3];
			R_move = moves[F * 3];
			L_move = moves[B * 3];
			break;
		case DF:
			F_move = moves[F * 3];
			R_move = moves[L * 3];
			L_move = moves[R * 3];
			break;
		case DL:
			F_move = moves[L * 3];
			R_move = moves[B * 3];
			L_move = moves[F * 3];
			break;
		case DB:
			F_move = moves[B * 3];
			R_move = moves[R * 3];
			L_move = moves[L * 3];
		}

		cube = second_to_last_step_algorithm(cube, F_move, R_move, L_move);
	}

	else {
		cube.doD(2); //Turn cube so what's in your face is the R face

		switch (next_edge) {
		case DB:
			F_move = moves[L * 3];
			R_move = moves[B * 3];
			L_move = moves[F * 3];
			break;
		case DF:
			F_move = moves[R * 3];
			R_move = moves[F * 3];
			L_move = moves[B * 3];
			break;
		case DL:
			F_move = moves[F * 3];
			R_move = moves[L * 3];
			L_move = moves[R * 3];
			break;
		case DR:
			F_move = moves[B * 3];
			R_move = moves[R * 3];
			L_move = moves[L * 3];
		}

		cube = second_to_last_step_algorithm(cube, F_move, R_move, L_move);
	}
	
	return cube;
}

cubie final(cubie cube) {
	bool match = false;
	short corner;
	for (short i = DFR; i <= DRB; i++) {
		if (cube.corn_perm[i] == i) {
			match = true;
			corner = i;
			break;
		}
	}

	do {
		cube.doL(2);
		cube.doF(2);
		cube.doL(3);
		cube.doB(3);
		cube.doL(1);
		cube.doF(2);
		cube.doL(3);
		cube.doB(1);
		cube.doL(3);

		for (short i = DFR; i <= DRB; i++) {
			if (cube.corn_perm[i] == i && cube.corn_ori[i] == 2) {
				match = true;
				corner = i;
				break;
			}
		}
	} while (match == false);

	cubie F_move;
	cubie L_move; 
	cubie B_move;

	cubie I;
	I.reset();

	std::array <cubie, 18> moves = make_moves();

	facelet a(cube.to_facelet_rep());
	a.to_2D_string();

	while (cube.compare(I) == false) {

		for (short i = DFR; i <= DRB; i++) {
			if (cube.corn_perm[i] == i && cube.corn_ori[i] == 2) {
				match = true;
				corner = i;
				break;
			}
		}


		short corn = cube.corn_perm[corner];

		switch (corn) {
		case DFR:
			F_move = moves[R * 3];
			L_move = moves[B * 3];
			B_move = moves[L * 3];
			break;
		case DLF:
			F_move = moves[F * 3];
			L_move = moves[R * 3];
			B_move = moves[B * 3];
			break;
		case DBL:
			F_move = moves[L * 3];
			L_move = moves[F * 3];
			B_move = moves[R * 3];
			break;
		case DRB:
			F_move = moves[B * 3];
			L_move = moves[L * 3];
			B_move = moves[F * 3];
			break;
		}

		cube = final_algorithm(cube, F_move, L_move, B_move);
	}
	
	return cube;

}

int solve(std::string facelet_rep) {
	facelet a("DDFRURLLBLFUDRLFLRBBDFFRUBRBUUUDFFBDFUURLDLFRDDBBBURLL");

	a.to_2D_string();

	//a.print_string();

	cubie c;
	c = a.to_cubie();

	c = white_cross(c);

	c = white_face(c);

	c = middle_layer(c);

	c = yellow_cross(c);

	c = second_to_last_step(c);

	//facelet b(c.to_facelet_rep());

	//b.to_2D_string();

	//c.output_cubie();

	//read_solution();

	c = final(c);

	//c.output_cubie();

	return 0;
}
