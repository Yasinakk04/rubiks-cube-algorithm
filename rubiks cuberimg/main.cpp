#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "enums.h"
#include "cubie.h"
#include "facelets.h"
#include "constants.h"
#include "miscellaneous functions.h"
#include "coord.h"

#include "moves.cpp"


const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

cubie cube = cubie();

int main() {


	//facelet a("UDDDUUUUUBBLLRRBLLRRRFFFRLLDUUUDDDDDFFFLLRBFFRRFBBBLBB");


	//cubie cube_4;
	//cube_4.set_ud_edges(19225);
	//cube_4.output_cubie_edges();

	//cubie cube_3;
	//cube_3.set_ud_edges(8270);
	//cube_3.output_cubie_edges();

	//cube1.edge_perm = { DR, BR, DL, UR, DB, BL, UF, FR, FL, UL, DF, UB };
	//std::cout << cube1.get_ud_slice_phase_1() << "\n";

	//cubie cube2;
	//cube2.edge_perm = { BR, UF, DL, DR, UR, DF, FR, FL, UL, DB, UB, BL };
	//std::cout << cube2.get_ud_slice_phase_1() << "\n";
	//	

	cubie cube3;
	cube3.edge_perm = { UF, DB, DF, UB, UR, DR, UL, DL, BL, FL, FR, BR };
	std::cout << cube3.get_ud_slice_phase_2();


	//cube.multiply(U_turn);
	//cube.multiply(D_turn); cube.multiply(D_turn); cube.multiply(D_turn);
	//cube.multiply(L_turn);
	//cube.multiply(B_turn); cube.multiply(B_turn);
	//cube.multiply(L_turn);
	//cube.multiply(U_turn); cube.multiply(U_turn); cube.multiply(U_turn);
	//cube.multiply(L_turn);
	//cube.multiply(F_turn);
	//cube.multiply(D_turn);
	//cube.multiply(B_turn);
	//cube.multiply(R_turn); cube.multiply(R_turn);
	//cube.multiply(D_turn); cube.multiply(D_turn);
	//cube.multiply(F_turn);
	//cube.multiply(D_turn); cube.multiply(D_turn);
	//cube.multiply(U_turn); cube.multiply(U_turn);
	//cube.multiply(F_turn); cube.multiply(F_turn); cube.multiply(F_turn);
	//cube.multiply(L_turn);
	//cube.multiply(R_turn); cube.multiply(R_turn); cube.multiply(R_turn);
	//cube.multiply(F_turn); cube.multiply(F_turn);
	//cube.multiply(R_turn); cube.multiply(R_turn);
	//cube.multiply(U_turn);
	//cube.multiply(D_turn); cube.multiply(D_turn); cube.multiply(D_turn);
	//cube.multiply(F_turn); cube.multiply(F_turn);
	//cube.multiply(L_turn); cube.multiply(L_turn);
	//cube.multiply(B_turn); cube.multiply(B_turn); cube.multiply(B_turn);
	//cube.output_cubie();
}
