#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>

#pragma comment(linker, "/STACK:8000000")

#include "enums.h"
#include "cubie.h"
#include "facelets.h"
#include "constants.h"
#include "miscellaneous functions.h"
#include "coord.h"
#include "symmetries.h"
#include "moves.h"


const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

cubie cube = cubie();

int main() {


	std::array <cubie, 48> symmetries = gen_symmetries();
	std::array <cubie, 48> inv_symmetries = gen_inv_symmetries(symmetries);

	//generate_twist_symmetry(symmetries, inv_symmetries);
	//generate_corner_symmetry_and_classes(symmetries, inv_symmetries);
	//generate_ud_edges_symmetry(symmetries, inv_symmetries);
	generate_flipslices_symmetry_and_classes(symmetries, inv_symmetries);


	std::cout << "Ok";
}