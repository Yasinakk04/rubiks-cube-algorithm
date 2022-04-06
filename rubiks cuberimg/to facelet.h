#pragma once
#include <array>

#include "enums.h"
#include "constants.h"
#include "cubie.h"
#include "facelets.h"


inline std::array <short, 54> cubie::to_facelet_rep(){
	unsigned short corner;
	unsigned short ori;
	std::array <short, 54> facelet_rep = {};
	facelet_rep.fill(0);

	for (short i = 0; i != 8; i++) {
		corner = corn_perm[i];
		ori = corn_ori[i];
		for (short j = 0; j != 3; j++) {
			facelet_rep[cornerFacelet[i][(j + ori) % 3]] = cornerColour[corner][j];
		}
	}

	unsigned short edge;

	for (short i = 0; i != 12; i++) {
		edge = edge_perm[i];
		ori = edge_ori[i];
		for (short j = 0; j != 2; j++) {
			facelet_rep[edgeFacelet[i][(j + ori) % 2]] = edgeColour[edge][j];
		}
	}

	for (short i = 0; i != 6; i++) {
		facelet_rep[9 * i + 4] = i;
	}

	return facelet_rep;
}