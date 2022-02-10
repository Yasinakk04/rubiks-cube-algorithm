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
	std::array <short, No_corner> corn_perm; //There are 8 corners and 12 edge pieces
	std::array <short, No_edge> edge_perm;

	std::array <short, No_corner> corn_ori;
	std::array <short, No_edge> edge_ori;

	void output_cubie_corners() {
		std::cout << "The corner positions are: \n";
		for (short i = 0; i != No_corner; i++) {
			std::string pos = corn_pos[i];
			if (corn_pos[i] == "-1") {
				std::cout << "Pos: " << pos << "\tCubie: " << corn_perm[i];
			}
			else {
				std::cout << "Pos: " << pos << "\tCubie: " << corn_pos[corn_perm[i]];
			}
			std::cout << "\tOrientation: " << corn_ori[i] << "\n";
		}
	}


	void output_cubie_edges(){
		std::cout << "\n\nThe edge positions are: \n";
		for (short i = 0; i != No_edge; i++) {
			std::string pos = edge_pos[i];
			if (edge_pos[i] == "-1") {
				std::cout << "Pos: " << pos << "\tCubie: " << edge_perm[i];
			}
			else {
				std::cout << "Pos: " << pos << "\tCubie: " << edge_pos[edge_perm[i]];
			}
			std::cout << "\tOrientation: " << edge_ori[i] << "\n";
		}
	}

	void output_cubie() {
		output_cubie_corners();
		output_cubie_edges();
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
		//for (short i = )


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

	void corner_multiply(cubie B) {
		short c_perm;
		short c_ori;

		for (short i = 0; i != No_corner; i++) {
			c_perm = corn_perm[B.corn_perm[i]];

			short oriA = corn_ori[B.corn_perm[i]];
			short oriB = B.corn_ori[i];

			if (oriA < 3 && oriB < 3) {
				//In this scenario neither
				//cube is a symmetry cube
				c_ori = oriA + oriB;
				if (c_ori >= 3) {
					//Non symmetry cubes can 
					//only multiply to produce other
					//non symmetry cubes
					//so the final orientation should be
					//between 0 and 2
					c_ori -= 3;
				}
			}

			else if (oriA < 3 && oriB >= 3) {
				//This is the scenario where A is a normal cube
				//and B is a symmetry cube
				c_ori = oriA + oriB;
				if (c_ori >= 6) {
					c_ori -= 3;
					//Products of symmetry cubes cannot take
					//values greater than 5
				}
			}

			else if (oriA >= 3 && oriB < 3) {
				//This is the scenario where A is a symmetry cube and
				//B is not
				c_ori = oriA - oriB;
				if (c_ori < 3) {
					c_ori += 3;
					//If the orientation were less than 3 
					//It would stop being a symmetry cube
					//which cannot be
				}
			}

			else if (oriA >= 3 && oriB > 3) {
				c_ori = oriA - oriB;
				if (c_ori < 0) {
					c_ori += 3;
					//The product of 2 symmetry cubes must be 1 
					//normal cube
					//so its orientation will be between 0 and 2
				}
			}

			corn_ori[i] = c_ori;
		}
	}
};

cubie U;
U.corn_perm = { 0,0,0,0,0,0,0,0 };

#endif
