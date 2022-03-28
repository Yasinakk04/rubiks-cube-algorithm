#pragma once


void solvePhase1() {
	//read file into array

	dist = flipslice_twist_depth[cube];

	while (flipslice_twist_depth[cube] != 0) {
		for (unsigned short i = 0; i != 18; i++) {
			cube.doMove[i];
			if (flipslice_twist_depth[cube] > dist) {
				continue;
			}
			else {
				break;
			}

		}
	}
 }