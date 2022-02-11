#pragma once

#include <iostream>
#include <string>
#include <array>
#include "enums.h"
#include "constants.h"
#include "cubie.h"
#

/*
The default facelet arrangement is as follows:

		  U1 U2 U3
		  U4 U5 U6
		  U7 U8 U9

L1 L2 L3  F1 F2 F3  R1 R2 R3
L4 L5 L6  F4 F5 F6  R4 R5 R6
L7 L8 L9  F7 F8 F9  R7 R8 R9

		  D1 D2 D3
		  D4 D5 D6
		  D7 D8 D9

		  B1 B2 B3
		  B4 B5 B6
		  B7 B8 B9
_________________________________

		  0  1  2
		  3  4  5
		  6  7  8

36 37 38  18 19 20  9  10 11
39 40 41  21 22 23  12 13 14
42 43 44  24 25 26  15 16 17

		  27 28 29
		  30 31 32
		  33 34 35

		  45 46 47
		  48 49 50
		  51 52 53
*/

class facelet {
public:
	std::array <short, 54> facelet_rep{};

	facelet(std::string face_string) {

		facelet_rep = from_string(face_string);
	}


	std::array<short, 54> from_string(std::string face_string) {	//facelets are defined in the odrer shown
																	//at the top
		std::array<short, 54> error{};
		std::array<short, 54> solved{};
		std::array<short, 54> facelet_rep{};

		for (int i = 0; i != 54; i++) { //The loop on the left defines a solved cube
			solved[i] = i / 9;		//This should save time in testing
		}

		if (face_string[0] == 'X') { //None of the faces are labelled X
			return solved;			//If I want to use the solved cube I can merely type X
		}


		else if (face_string.length() != 54) {
			std::cout << "Invalid cube, more or less than 54 facelets\n\n";
			//There are exactly 54 facelets on a cube
			return error;
		}


		else {
			int count[] = { 0, 0, 0, 0, 0, 0 }; //Each member of the array counts 
											//the number of each facelet colour
			for (int i = 0; i != 54; i++) {
				if (face_string[i] == 'U') {
					facelet_rep[i] = U; count[U]++;
				}
				else if (face_string[i] == 'R') {
					facelet_rep[i] = R; count[R]++;
				}
				else if (face_string[i] == 'F') {
					facelet_rep[i] = F; count[F]++;
				}
				else if (face_string[i] == 'D') {
					facelet_rep[i] = D; count[D]++;
				}
				else if (face_string[i] == 'L') {
					facelet_rep[i] = L; count[L]++;
				}
				else if (face_string[i] == 'B') {
					facelet_rep[i] = B; count[B]++;
				}
				else {
					return error;
					break;
				}
			}

			for (int i = 0; i != 6; i++) {
				if (count[i] != 9) {
					std::cout << "more or less than 9 of some colour\n\n";
					return error;
				}
			}
			return facelet_rep;
		}
	}

	void to_2D_string() {

		std::array <std::string, 54> string_2D; //This defines an array of strings
		std::array <char, 54> colours_2D;

		for (int i = 0; i != 54; i++) {
			string_2D[i] = std::to_string(facelet_rep[i]); //This loops through the arrays and 
															//assigns each index that of the other as
															// a string over a short

			if (string_2D[i].length() == 1) {				//On the left it checks the length of 
				string_2D[i] = "0" + string_2D[i];			//the index. If it's 1 it adds a 0
			}												//This should help with testing

			short colour = facelet_rep[i];					//The facelets are grouped by colour
			if (colour == U) { colours_2D[i] = 'U'; }		//This means by calculator how many times
			else if (colour == R) { colours_2D[i] = 'R'; }  //9 goes into the value you can find the 
			else if (colour == F) { colours_2D[i] = 'F'; }  //colour
			else if (colour == L) { colours_2D[i] = 'L'; }
			else if (colour == D) { colours_2D[i] = 'D'; }
			else if (colour == B) { colours_2D[i] = 'B'; }

		}

		std::cout <<
			"         " << string_2D[0] << " " << string_2D[1] << " " << string_2D[2] << "\n" << \
			"         " << string_2D[3] << " " << string_2D[4] << " " << string_2D[5] << "\n" << \
			"         " << string_2D[6] << " " << string_2D[7] << " " << string_2D[8] << "\n" << \
			\
			string_2D[36] << " " << string_2D[37] << " " << string_2D[38] << " " << string_2D[18] << " " << string_2D[19] << " " << string_2D[20] << " " << string_2D[9] << " " << string_2D[10] << " " << string_2D[11] << "\n" << \
			string_2D[39] << " " << string_2D[40] << " " << string_2D[41] << " " << string_2D[18] << " " << string_2D[22] << " " << string_2D[23] << " " << string_2D[12] << " " << string_2D[13] << " " << string_2D[14] << "\n" << \
			string_2D[42] << " " << string_2D[43] << " " << string_2D[41] << " " << string_2D[24] << " " << string_2D[25] << " " << string_2D[26] << " " << string_2D[15] << " " << string_2D[16] << " " << string_2D[17] << "\n" << \
			\
			"         " << string_2D[27] << " " << string_2D[28] << " " << string_2D[29] << "\n" << \
			"         " << string_2D[30] << " " << string_2D[31] << " " << string_2D[32] << "\n" << \
			"         " << string_2D[33] << " " << string_2D[34] << " " << string_2D[35] << "\n" << \
			\
			"         " << string_2D[45] << " " << string_2D[46] << " " << string_2D[47] << "\n" << \
			"         " << string_2D[48] << " " << string_2D[49] << " " << string_2D[50] << "\n" << \
			"         " << string_2D[51] << " " << string_2D[52] << " " << string_2D[53] << "\n";


		std::cout <<
			"\n\n      " << colours_2D[0] << " " << colours_2D[1] << " " << colours_2D[2] << "\n" << \
			"      " << colours_2D[3] << " " << colours_2D[4] << " " << colours_2D[5] << "\n" << \
			"      " << colours_2D[6] << " " << colours_2D[7] << " " << colours_2D[8] << "\n" << \
			\
			colours_2D[36] << " " << colours_2D[37] << " " << colours_2D[38] << " " << colours_2D[18] << " " << colours_2D[19] << " " << colours_2D[20] << " " << colours_2D[9] << " " << colours_2D[10] << " " << colours_2D[11] << "\n" << \
			colours_2D[39] << " " << colours_2D[40] << " " << colours_2D[41] << " " << colours_2D[18] << " " << colours_2D[22] << " " << colours_2D[23] << " " << colours_2D[12] << " " << colours_2D[13] << " " << colours_2D[14] << "\n" << \
			colours_2D[42] << " " << colours_2D[43] << " " << colours_2D[41] << " " << colours_2D[24] << " " << colours_2D[25] << " " << colours_2D[26] << " " << colours_2D[15] << " " << colours_2D[16] << " " << colours_2D[17] << "\n" << \
			\
			"      " << colours_2D[27] << " " << colours_2D[28] << " " << colours_2D[29] << "\n" << \
			"      " << colours_2D[30] << " " << colours_2D[31] << " " << colours_2D[32] << "\n" << \
			"      " << colours_2D[33] << " " << colours_2D[34] << " " << colours_2D[35] << "\n" << \
			\
			"      " << colours_2D[45] << " " << colours_2D[46] << " " << colours_2D[47] << "\n" << \
			"      " << colours_2D[48] << " " << colours_2D[49] << " " << colours_2D[50] << "\n" << \
			"      " << colours_2D[51] << " " << colours_2D[52] << " " << colours_2D[53] << "\n";

	}

	cubie to_cubie() {
		cubie cc{};
		cc.corn_perm.fill(-1);
		cc.edge_perm.fill(-1);


		//The above invalidates the permutation after it is initialised


		//Calculating the corner cubie arrangement 
		short ori{};
		bool corner_check;

		for (short i = 0; i != No_corner; i++) {

			std::array <short, 3> face = cornerFacelet[i];
			corner_check = false;



			for (short j = 0; j != 3; j++) {
				if (facelet_rep[face[j]] == U or facelet_rep[face[j]] == D) { ori = j; break; }
				//The above is to figure out which facelet of a corner is a U or D facelet
				//At least one of them are


				//The below should only occur after each of the corner facelets has been checked 
				//to see if it is U or D
				else if (j == 2) { std::cout << "The entered corners are invalid\n i is " << i << "\nj is " << j; return cc; }
				//If none of the faces are a U or a D then there must have been an error
			}

			short colour1 = facelet_rep[face[(ori + 1) % 3]];
			short colour2 = facelet_rep[face[(ori + 2) % 3]];
			//The 2 adjacent facelets to the U or D face are defined above

			for (short j = 0; j != No_corner; j++) {
				if (colour1 == cornerColour[j][1] && colour2 == cornerColour[j][2]) {
					cc.corn_perm[i] = j;
					cc.corn_ori[i] = ori;
					corner_check = true;
					break;
				}
			}

			if (corner_check == false) {
				std::cout << "corner at position " << i << " is invalid\n";
				return cc;
			}

			//The above for loop goes through each of the corners and checks which of the  
			//possible corners matches the facelet arrangement 
		}

		//std::cout << "The corners were valid\n\n";



		//Calculating the edge cubie arrangement 
		for (short k = 0; k != No_edge; k++) { //This first loop is to loop through each 
											//cubie position


			//std::cout << k << "\n";
			bool edge_check = false;
			//This variable is used to check if an edge is or isn't present


			for (short l = 0; l != No_edge; l++) {  //The second loop is to loop through each
													//possible edge colour combination
													// or cubie
				if (facelet_rep[(edgeFacelet[k][0])] == edgeColour[l][0] && 
					facelet_rep[(edgeFacelet[k][1])] == edgeColour[l][1]) {

					cc.edge_perm[k] = l;
					cc.edge_ori[k] = 0;

					edge_check = true;
					break;
				}

				else if (facelet_rep[(edgeFacelet[k][1])] == edgeColour[l][0] && 
					facelet_rep[(edgeFacelet[k][0])] == edgeColour[l][1]) {

					cc.edge_perm[k] = l;
					cc.edge_ori[k] = 1;

					edge_check = true;
					break;
				}

				//Edge cubies can only take 2 different possible orientations
				//so it is easier to calculate the orientation by listing the edge facelets
				//In a particular order
				//depending on the actual order it tells you if they're 
				//orientated or not
			}

			if (edge_check == false) {
				std::cout << "Edge " << k << " has not been defined \n\n";
				return cc;
			}
		}
		return cc;
	}
};