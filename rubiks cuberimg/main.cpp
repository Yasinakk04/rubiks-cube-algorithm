#include <iostream>
#include <string>
#include <array>

#include "enums.h"
#include "cubie.h"
#include "facelets.h"
#include "constants.h"
#include "miscellaneous functions.h"

const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

int main() {
	//facelet a("X");

	//cubie cube = a.to_cubie();

//	std::cout << cube.get_twist();

	//std::cout << cube.get_flip();

	std::cout << b_coefficient(5, 2);
}