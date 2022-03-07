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

	//std::ofstream myfile;
	//myfile.open("a.dat");

	//std::array <short, 10> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	//for (int i = 0; i != 10; i++) {
	//	myfile << x[i];
	//}

	//std::ifstream myfile;
	//myfile.open("a.dat");

	//
	//for (int i = 0; i != 10; i++) {
	//	k = myfile.get();
	//	std::cout << k << "\n";
	//}

	std::array <unsigned short, 2187 * 18> twist_table;

	std::ifstream myfile;
	myfile.open("twist move table.txt");

	int index = 0;

	while (index != 39366) {
		unsigned short k;
		myfile >> k;
		k--;
		twist_table[index] = k;
		
		index++;
	}


	//cubie c;
	//std::cout << twist_table[0] << "\n";

	//c.set_twist(twist_table[0]);
	//c.output_cubie();


	//c.set_twist(65534);
	//c.output_cubie();

	//std::cout << c.get_twist();











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
