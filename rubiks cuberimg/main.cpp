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

	make_flip_table();

	std::array <unsigned short, 2048 * 18> flip_table;

	std::ifstream myfile;
	myfile.open("flip move table.bin");


	for (unsigned short i = 0; i != 2048 * 18; i++) {
		myfile.read((char*)&(flip_table[i]), 2);
	}
	myfile.close();
	std::cout << flip_table[464];

	//unsigned short x;

	//x = flip_table[U * 3];
	//x = flip_table[18 * x + D * 3 + 2];
	//x = flip_table[18 * x + L * 3];
	//x = flip_table[18 * x + B * 3 + 1];
	//x = flip_table[18 * x + L * 3];
	//x = flip_table[18 * x + U * 3 + 2];
	//x = flip_table[18 * x + L * 3];
	//x = flip_table[18 * x + F * 3];
	//std::cout << x << " before\n\n";
	//x = flip_table[18 * x + D * 3];
	//std::cout << x << " after \n\n";
	// 
	// 
	
	//x = flip_table[18 * x + B * 3];
	//x = flip_table[18 * x + R * 3 + 1];
	//x = flip_table[18 * x + D * 3 + 1];
	//x = flip_table[18 * x + F * 3];
	//x = flip_table[18 * x + D * 3 + 1];
	//x = flip_table[18 * x + U * 3 + 1];
	//x = flip_table[18 * x + F * 3 + 2];
	//x = flip_table[18 * x + L * 3];
	//x = flip_table[18 * x + R * 3 + 2];
	//x = flip_table[18 * x + F * 3 + 1];
	//x = flip_table[18 * x + R * 3 + 1];
	//x = flip_table[18 * x + U * 3];
	//x = flip_table[18 * x + D * 3 + 2];
	//x = flip_table[18 * x + F * 3 + 1];
	//x = flip_table[18 * x + L * 3 + 1];
	//x = flip_table[18 * x + B * 3 + 2];


	cubie c;

	//c.set_flip(x);
	//c.output_cubie();







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
	////cube4.output_cubie_edges();
	//cubie cube;
	//cube.reset();
	//std::array <cubie, 18> moves = make_moves();

	//cube.multiply(moves[U * 3]);
	//cube.multiply(moves[D * 3 + 2]);
	//cube.multiply(moves[L * 3]);
	//cube.multiply(moves[B * 3 + 1]);
	//cube.multiply(moves[L * 3]);
	//cube.multiply(moves[U * 3 + 2]);
	//cube.multiply(moves[L * 3]);
	//cube.multiply(moves[F * 3]);
	//cube.multiply(moves[D * 3]);
	//cube.multiply(moves[B * 3]);
	//cube.multiply(moves[R * 3 + 1]);
	//cube.multiply(moves[D * 3 + 1]);
	//cube.multiply(moves[F * 3]);
	//cube.multiply(moves[D * 3 + 1]);
	//cube.multiply(moves[U * 3 + 1]);
	//cube.multiply(moves[F * 3 + 2]);
	//cube.multiply(moves[L * 3]);
	//cube.multiply(moves[R * 3 + 2]);
	//cube.multiply(moves[F * 3 + 1]);
	//cube.multiply(moves[R * 3 + 1]);
	//cube.multiply(moves[U * 3]);
	//cube.multiply(moves[D * 3 + 2]);
	//cube.multiply(moves[F * 3 + 1]);
	//cube.multiply(moves[L * 3 + 1]);
	//cube.multiply(moves[B * 3 + 2]);
	//cube.output_cubie();
}
