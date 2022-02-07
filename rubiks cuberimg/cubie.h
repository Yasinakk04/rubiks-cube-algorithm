#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <array>
#include "miscellaneous functions.h"
#include "enums.h"
#include "constants.h"
//#include "facelets.h"


class cubie {
public:
	std::array <short, 8> corn_perm; //There are 8 corners and 12 edge pieces
	std::array <short, 12> edge_perm;

	std::array <short, 8> corn_ori;
	std::array <short, 12> edge_ori;

	void output_cubie() {
		std::cout << "The corner positions are: \n";
		for (short i = 0; i != No_corner; i++) {
			std::string pos = corn_pos[i];
			std::cout << "Pos: " << pos << "\tCubie: " << corn_perm[i];
			std::cout << "\tOrientation: " << corn_ori[i] << "\n";
		}

		std::cout << "\n\nThe edge positions are: \n";
		for (short i = 0; i != No_edge; i++) {
			std::string pos = edge_pos[i];
			std::cout << "Pos: " << pos << "\tCubie: " << edge_perm[i];
			std::cout << "\tOrientation: " << edge_ori[i] << "\n";
		}
	}

	short get_twist() {
		short twist = 0;
		for (short i = 6; i != 0; i--) {
			twist = short_pow(short (corn_ori[6 - i]), i) + twist;
		}
		return twist;
	}

	short get_flip() {
		short flip = 0;
		for (short i = 10; i != 0; i--) {
			flip = short_pow(short (edge_ori[10 - i]), i) + flip;
		}
		return flip;
	}


	//The purpose of this function is only to determine 
	//if edges for the middle slice (ud slice)
	//are there or not
	short get_ud_slice() {
		short ud_slice = 0;
		for (short i = )


	}

	void get_corners() {

	}

	void get_ud_slice_sorted() {

	}

	void get_ud_edges() {

	}

	//SSSSSSSSSEEEEEEETTTTTTTTTTTTEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRRRRSSSSSSSSSSSSSSSS

	void set_twist() {

	}

	void set_flip() {

	}

	void set_ud_slice() {

	}

	void set_corners() {

	}

	void set_ud_slice_sorted() {

	}

	void set_ud_edges() {

	}

	void multiply() {



	}
};



#endif
