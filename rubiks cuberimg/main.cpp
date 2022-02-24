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


	cubie a;
	a.corn_perm = {URF,UFL,UBR,DRB,DLF,DFR,ULB,DBL};

	a.set_corners(35642);
	//std::cout << a.get_corners_with_rotation() << std::endl;

	a.output_cubie_corners();



	//std::vector <short> something = { URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB };

	//something = rotate_left(something, 0, 6);

	//for (short i = 0; i != something.size(); i++) {
	//	std::cout << corn_pos[something[i]] << ", ";
	//}


	//cube.set_corn_perm({});
	//facelet a("X");

	//facelet cube1("URBLUDRRURRLLRBUBFDBFUFFBBLLLFFDDRFLBDFDLLDUDBRDFDURUU");

	//facelet cube2("LRDDURRFLUBFLRLBRRDUFBFUUDDBFLFDURFUBLFULDDRRBLFBBBUDL");
	/*
	cubie cube;
	cube.edge_perm = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	std::cout << cube.get_ud_slice_phase_2();*/

	//cube.edge_multiply(F_turn);

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
