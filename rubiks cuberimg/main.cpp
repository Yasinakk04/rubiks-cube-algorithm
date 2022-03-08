#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>

#include "enums.h"
#include "cubie.h"
#include "facelets.h"
#include "constants.h"
#include "miscellaneous functions.h"
#include "coord.h"

#include "moves.h"


const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

cubie cube = cubie();

int main() {



	//facelet a("URBLUDRRURRLLRBUBFDBFUFFBBLLLFFDDRFLBDFDLLDUDBRDFDURUU");
	//cubie c = a.to_cubie();
	//c.output_cubie();





	

	////////std::ifstream something("a.bin", std::ios::binary);

	////////short a;
	////////something.read((char*)&a, 2);
	////////something.close();
	////////std::cout << a;


	std::array <unsigned short, 2048 * 18> flip_table;

	std::ifstream myfile;
	myfile.open("flip move table.bin");


	for (unsigned short i = 0; i != 2048 * 18; i++) {
		myfile.read((char*)&(flip_table[i]), 2);
	}
	myfile.close();

	short x;

	x = flip_table[B];
	x = flip_table[x * 18 + D3];
	x = flip_table[x * 18 + L];
	x = flip_table[x * 18 + B2];
	x = flip_table[x * 18 + L];
	x = flip_table[x * 18 + U3];
	x = flip_table[x * 18 + L];
	x = flip_table[x * 18 + F];
	x = flip_table[x * 18 + D];
	x = flip_table[x * 18 + B];
	x = flip_table[x * 18 + R2];
	x = flip_table[x * 18 + D2];
	x = flip_table[x * 18 + F];
	x = flip_table[x * 18 + D2];
	x = flip_table[x * 18 + U2];
	x = flip_table[x * 18 + F3];
	x = flip_table[x * 18 + L];
	x = flip_table[x * 18 + R3];
	x = flip_table[x * 18 + F2];
	x = flip_table[x * 18 + R2];
	x = flip_table[x * 18 + U];
	x = flip_table[x * 18 + D3];
	x = flip_table[x * 18 + F2];
	x = flip_table[x * 18 + L2];
	x = flip_table[x * 18 + B3];

	cubie c;

	c.set_flip(137);
	c.output_cubie();
	std::cout << x;







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


	//test();


	//cubie cube3;
	//cube3.set_ud_slice_phase_2(3);
	//cube3.output_cubie_edges();


	//cubie cube4;
	//cube4.set_ud_slice_phase_2(1);
	//cube4.output_cubie_edges();

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
