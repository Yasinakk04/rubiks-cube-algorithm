#pragma once
#include "enums.h"

#include "cubie.h"
#include "moves.h"
#include "place edge in right place.h"

void white_cross(cubie cube){
	std::array <cubie, 18> moves = make_moves();

	if (cube.edge_perm[0] != 0 || cube.edge_ori[0] != 0			//This checks if there is already
		|| cube.edge_perm[1] != 1 || cube.edge_ori[1] != 0			//a white cross or not
		|| cube.edge_perm[2] != 2 || cube.edge_ori[2] != 0
		|| cube.edge_perm[3] != 3 || cube.edge_ori[3] != 0) {

		cube.put_U_edge_in_U_face(UR);

		cube.output_cubie_edges();

		cube.put_U_edge_in_U_face(UL);

		cube.output_cubie_edges();

		cube.put_U_edge_in_U_face(UF);

		cube.output_cubie_edges();

		cube.put_U_edge_in_U_face(UB);
		
		cube.output_cubie_edges();
	}
}

