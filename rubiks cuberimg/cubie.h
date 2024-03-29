#pragma once

#include <iostream>
#include <array>
#include <vector>

#include "miscellaneous functions.h"
#include "enums.h"
#include "constants.h"

class cubie {
public:

	std::array <short, No_corner> corn_perm; //There are 8 corners and 12 edge pieces
	std::array <short, No_edge> edge_perm;

	std::array <short, No_corner> corn_ori;
	std::array <short, No_edge> edge_ori;
public:
	cubie() {
		corn_perm = { 0, 1, 2, 3, 4, 5, 6, 7 };
		corn_ori = { 0, 0, 0, 0, 0, 0, 0, 0 };

		edge_perm = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		edge_ori = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	}

	cubie(std::array <short, 8> c_perm,
		std::array <short, 8> c_ori,
		std::array <short, 12> e_perm,
		std::array <short, 12> e_ori) {
		corn_perm = c_perm;
		corn_ori = c_ori;

		edge_perm = e_perm;
		edge_ori = e_ori;
	}


	// ------------------------------------------------
	//set cube attributes
	void set_corn_perm(std::array <short, No_corner> cp) {
		corn_perm = cp;
	}

	void set_edge_perm(std::array <short, No_edge> ep) {
		edge_perm = ep;
	}

	void set_corn_ori(std::array <short, No_corner> co) {
		corn_ori = co;
	}

	void set_edge_ori(std::array <short, No_edge> eo) {
		edge_ori = eo;
	}
	// ------------------------------------------------

	void output_cubie_corners() {
		std::cout << "The corner positions are: \n";
		for (short i = 0; i != No_corner; i++) {
			std::string pos = corn_pos[i];
			if (corn_perm[i] == -1) {
				std::cout << "Pos: " << pos << "\tCubie: " << corn_perm[i];
			}
			else {
				std::cout << "Pos: " << pos << "\tCubie: " << corn_pos[corn_perm[i]];
			}
			std::cout << "\tOrientation: " << corn_ori[i] << "\n";
		}
		std::cout << "\n";
	}


	void output_cubie_edges() {
		std::cout << "\nThe edge positions are: \n";
		for (short i = 0; i != No_edge; i++) {
			std::string pos = edge_pos[i];
			if (edge_perm[i] == -1) {
				std::cout << "Pos: " << pos << "\tCubie: " << edge_perm[i];
			}
			else if (edge_perm[i] == 12) {
				std::cout << "Pos: " << pos << "\tCubie: " << "UD edge";
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
		std::cout << "\n\n";
	}


	void corner_multiply(cubie B) {
		std::array <short, 8> c_ori{};
		std::array <short, 8> c_perm{};

		for (short i = 0; i != No_corner; i++) {


			c_perm[i] = corn_perm[B.corn_perm[i]];

			short oriA = corn_ori[B.corn_perm[i]];
			short oriB = B.corn_ori[i];

			if (oriA < 3 && oriB < 3) {
				//In this scenario neither
				//cube is a symmetry cube
				c_ori[i] = oriA + oriB;
				if (c_ori[i] >= 3) {
					//Non symmetry cubes can
					//only multiply to produce other
					//non symmetry cubes
					//so the final orientation should be
					//between 0 and 2
					c_ori[i] -= 3;
				}
			}

			else if (oriA < 3 && oriB >= 3) {
				//This is the scenario where A is a normal cube
				//and B is a symmetry cube
				c_ori[i] = oriA + oriB;
				if (c_ori[i] >= 6) {
					c_ori[i] -= 3;
					//Products of symmetry cubes cannot take
					//values greater than 5
				}
			}

			else if (oriA >= 3 && oriB < 3) {
				//This is the scenario where A is a symmetry cube and
				//B is not
				c_ori[i] = oriA - oriB;
				if (c_ori[i] < 3) {
					c_ori[i] += 3;
					//If the orientation were less than 3
					//It would stop being a symmetry cube
					//which cannot be
				}
			}

			else if (oriA >= 3 && oriB > 3) {
				c_ori[i] = oriA - oriB;
				if (c_ori[i] < 0) {
					c_ori[i] += 3;
					//The product of 2 symmetry cubes must be 1
					//normal cube
					//so its orientation will be between 0 and 2
				}
			}
		}

		for (short i = 0; i != 8; i++) {
			corn_ori[i] = c_ori[i];
			corn_perm[i] = c_perm[i];
		}
	}

	void edge_multiply(cubie B) {
		std::array <short, 12> e_ori{};
		std::array <short, 12> e_perm{};

		e_ori.fill(0);
		e_perm.fill(0);

		for (short i = 0; i != No_edge; i++) {
			e_perm[i] = edge_perm[B.edge_perm[i]];
			e_ori[i] = (B.edge_ori[i] + edge_ori[B.edge_perm[i]]) % 2;
		}

		for (short i = 0; i != No_edge; i++) {
			edge_perm[i] = e_perm[i];
			edge_ori[i] = e_ori[i];
		}
	}

	void multiply(cubie B) {
		corner_multiply(B);
		edge_multiply(B);
	}

	void reset() {
		corn_perm = { 0, 1, 2, 3, 4, 5, 6, 7 };						//This is the permutation of a solved rubik's cube
		corn_ori = { 0, 0, 0, 0, 0, 0, 0, 0 };

		edge_perm = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		edge_ori = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	}

	bool compare(cubie b) {

		for (short i = 0; i != 8; i++) {
			if (corn_perm[i] != b.corn_perm[i] || corn_ori[i] != b.corn_ori[i]) {		//This functions goes throuhg each corner and
				return false;															//edge for 2 cubes
			}																			//returning false if any of them don't match
		}

		for (short i = 0; i != 12; i++) {
			if (edge_perm[i] != b.edge_perm[i] || edge_ori[i] != b.edge_ori[i]) {
				return false;
			}
		}

		return true;
	}

	// ------------------------------------------------

	short find_edge_pos(short edge) {
		for (char i = 0; i != 12; i++) {
			if (edge_perm[i] == edge) {		//Each of the 4 functions here perform a linear search to find
				return i;					//the location of the edge or the corner and its orientation
			}
		}
	}

	short find_edge_ori(short edge) {
		for (char i = 0; i != 12; i++) {
			if (edge_perm[i] == edge) {
				return edge_ori[i];
			}
		}
	}

	short find_corner_pos(short corner) {
		for (char i = 0; i != 8; i++) {
			if (corn_perm[i] == corner) {
				return i;
			}
		}
	}

	short find_corner_ori(short corner) {
		for (char i = 0; i != 8; i++) {
			if (corn_perm[i] == corner) {
				return corn_ori[i];
			}
		}
	}

	// ------------------------------------------------

	bool corner_in_U_face(short corner) {
		if (find_corner_pos(corner) <= UBR) {	//UBR is the last U corner
			return true;						//if its position is less than it it must be in the U face
		}
		else {
			return false;
		}
	}

	bool corner_in_F_face(short corner) {
		if (find_corner_pos(corner) <= UFL ||	//The corners are specified by U face first then D face
			find_corner_pos(corner) == DFR ||	//so here it was necessary to specify each individually
			find_corner_pos(corner) == DLF) {	//except the first 2 corners
			return true;
		}
		else {
			return false;
		}
	}

	bool corner_in_D_face(short corner) {
		if (corner_in_U_face(corner) == false) {	//this should be self explanatory
			return true;							//if a corner is not in the U face it's in the 
		}											//D face by default
		else {
			return false;
		}
	}

	bool corner_in_B_face(short corner) {
		if (corner_in_F_face(corner) == false) {	//as with this
			return true;
		}
		else {
			return false;
		}
	}

	// ------------------------------------------------

	bool edge_in_U_face(short edge) {
		if (find_edge_pos(edge) <= UB) {	//the last U edge is UB so if it's less than that it must be in the U face
			return true;
		}
		else {
			return false;
		}
	}

	bool edge_in_R_face(short edge) {
		short edge_pos = find_edge_pos(edge);		//Here each of the R edges are enumerated
		if (edge_pos == UR ||
			edge_pos == FR ||
			edge_pos == BR ||
			edge_pos == DR) {
			return true;
		}
		else {
			return false;
		}
	}

	bool edge_in_F_face(short edge) {
		unsigned short edge_pos = find_edge_pos(edge);		//here each of the F edges are enumerated
		if (edge_pos == UF ||
			edge_pos == FR ||
			edge_pos == FL ||
			edge_pos == DF) {
			return true;
		}
		else {
			return false;
		}
	}

	bool edge_in_D_face(short edge) {
		if (DR <= find_edge_pos(edge) && find_edge_pos(edge) <= DB) {		//Here it checks the edge is between the start and end D edge
			return true;
		}
		else {
			return false;
		}
	}

	bool edge_in_L_face(short edge) {							//here it enumerates each of the L edges
		unsigned short edge_pos = find_edge_pos(edge);
		if (edge_pos == UL ||
			edge_pos == FL ||
			edge_pos == BL ||
			edge_pos == DL) {
			return true;
		}
		else {
			return false;
		}
	}

	bool edge_in_B_face(short edge) {							//Here each of the B edges are enumerated
		unsigned short edge_pos = find_edge_pos(edge);
		if (edge_pos == UB ||
			edge_pos == BR ||
			edge_pos == BL ||
			edge_pos == DB) {
			return true;
		}
		else {
			return false;
		}
	}

	// ------------------------------------------------

	void put_edge_in_D_face(short edge);				//Each of these methods have to be declared here

	void put_U_corner_in_DBR(short corner);				//in order to prevent a linking error

	// ------------------------------------------------

	void check_U_edge_in_pos(short e_pos);

	// ------------------------------------------------

	void put_U_edge_in_U_face(short edge);

	void put_U_corner_in_U_face(short corner);

	// ------------------------------------------------

	void doU(int times);
	void doR(int times);
	void doF(int times);
	void doD(int times);
	void doL(int times);
	void doB(int times);

	void do_move_vector(std::vector <short> a_moves) {		//this function accepts an algorithm as a vector
		cubie I;											//and performs moves on the cube based on the values in the vector
		for (short i = 0; i != a_moves.size(); i++) {
			switch (a_moves[i]) {
			case U:
				doU(1);
				break;
			case R:
				doR(1);
				break;
			case F:
				doF(1);
				break;
			case D:
				doD(1);
				break;
			case L:
				doL(1);
				break;
			case B:
				doB(1);
				break;
			default:
				std::cout << "error";
				break;
			}
		}
	}

	// ------------------------------------------------
	std::array <short, 54> to_facelet_rep();

	// ------------------------------------------------

	unsigned short get_twist() {
		unsigned short twist = 0;
		for (short i = 0; i != 7; i++) {
			twist = 3 * twist + corn_ori[i];
		}
		//The for loop doesn't need to go from 7 to 0 as the
		//orientation of the last corner can
		//be determined by the sum of the other corners
		//as the total must be a multiple of 3

		return twist;
	}

	void set_twist(unsigned short twist_val) {
		short ori_sum = 0;
		short ori;
		for (short i = 6; i != -1; i--) {
			//if you think about the twist value
			//as a ternary number
			//doing mod 3 gives us the last digit
			ori = twist_val % 3;
			corn_ori[i] = ori;
			ori_sum += ori;
			twist_val /= 3;
		}

		if (ori_sum % 3 == 0) { corn_ori[7] = 0; }

		else { corn_ori[7] = 3 - (ori_sum % 3); }
	}

	// ------------------------------------------------
	unsigned short get_flip() {
		short flip = 0;
		for (short i = 0; i != 11; i++) {
			flip = 2 * flip + edge_ori[i];
		}
		//similar to the get_twist function
		//The sum of the orientations is a multiple of 2
		//so we can ignore the last edge

		return flip;
	}

	void set_flip(unsigned short flip_val) {
		unsigned short flip_sum = 0;
		unsigned short flip;
		for (short i = 10; i != -1; i--) {
			flip = flip_val % 2;
			edge_ori[i] = flip;
			flip_sum += flip;
			flip_val /= 2;
		}

		edge_ori[11] = flip_sum % 2;
	}

	// ------------------------------------------------
	unsigned short get_corners() {
		unsigned short corners_val = 0;
		short count;
		for (short i = DRB; i != URF; i--) {
			//You ignore the corner in position 0
			//as there's nothing left of it

			count = 0;
			for (short j = 0; j != i; j++) {
				if (corn_perm[j] > corn_perm[i]) {
					count++;
				}
			}
			corners_val = i * (count + corners_val);
		}

		//Kociemba defines the natural corner order as
		//URF<UFL<ULB<UBR<DFR<DLF<DBL<DRB
		//The corners are from positions URF to DRB
		//in the corn_perm array
		//for each corner, if any corner left of it
		//follows this order a count is incremented
		//ie if DRB is left or URF then it will
		//be incremented
		//the total count is then multiply by the
		//factorial for that corner

		return corners_val;
	}

	void set_corners(unsigned short corners_val) {
		std::array <short, 7> corn_coord_array{};
		corn_perm.fill(-1);

		for (short i = 2; i != 9; i++) {
			corn_coord_array[i - 2] = corners_val % (i);
			corners_val /= (i);
		}

		std::vector <short> values = { URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB };
		std::vector <short> values2 = { 7, 6, 5, 4, 3, 2, 1, 0 };

		for (short i = DRB - 1; i != URF - 1; i--) {
			for (short j = 0; j != 8; j++) {


				if (corn_coord_array[i] == values2[j]) {

					corn_perm[i + 1] = values[j];

					values2[j] = -1;

					for (short x = j - 1; x != -1; x--) {
						values2[x]--;
					}
					break;
				}
			}
		}

		for (short i = 0; i != 8; i++) {
			if (values2[i] >= 0) {
				corn_perm[0] = values[i];
				break;
			}
		}
	}

	// ------------------------------------------------

	//The below function outputs just the locations
	//of the middle slice edges as a number
	//The value won't tell you what edge is in what place
	//Just that these ud slice edges are in these places
	short get_ud_slice_phase_1() {
		short ud_slice_phase_1 = 0;
		short k = -1;
		for (short i = 0; i != No_edge; i++) {
			if (edge_perm[i] >= FR) {
				k++;
			}
			else {
				ud_slice_phase_1 += b_coefficient(i, k);
			}
		}

		return ud_slice_phase_1;
	}

	void set_ud_slice_phase_1(short ud_slice_value) {
		short n = 3;
		short x;
		unsigned short y = 8;
		edge_perm.fill(-1);

		for (short i = BR; i != -1; i--) {
			x = b_coefficient(i, n);
			if (ud_slice_value >= x) {
				ud_slice_value -= x;
			}
			else {
				edge_perm[i] = y;
				n--;
				y++;
			}

			if (n == -1) { break; }
		}

		x = 0;

		for (short i = BR; i != -1; i--) {
			if (edge_perm[i] < 0) {
				edge_perm[i] = x;
				x++;
			}
		}
	}

	//Phase one places all the ud edges in the ud slice
	//Phase two places them into the correct place
	short get_ud_slice_phase_2() {
		std::vector <short> ud_edge = { 0, 0, 0, 0 };
		short j = 0;
		unsigned short ud_edge_pos = 0;

		//This for loop is used to give a unique value for the
		//ud edge cubies. In phase 2 it will always evaluate to
		//0 as all the cubies are in the correct slice
		for (short i = 0; i != No_edge; i++) {
			if (edge_perm[i] >= FR) {
				ud_edge[j] = edge_perm[i];
				j++;
			}
			else {
				ud_edge_pos = ud_edge_pos + b_coefficient(i, j - 1);
				//in the first function k starts as -1
				//so subtracting 1 isn't necessary
			}
		}

		unsigned short ud_slice_phase_2 = 0;
		short rotations;
		for (short i = 3; i != 0; i--) {
			rotations = 0;
			while (ud_edge[i] != i + 8) {
				ud_edge = rotate_left(ud_edge, 0, i);
				rotations++;
			}
			ud_slice_phase_2 = (i + 1) * ud_slice_phase_2 + rotations;
		}

		ud_slice_phase_2 = 24 * ud_edge_pos + ud_slice_phase_2;


		return ud_slice_phase_2;
	}

	void set_ud_slice_phase_2(unsigned short ud_slice_phase_2_value) {

		unsigned short pos = ud_slice_phase_2_value / 24;
		unsigned short perm = ud_slice_phase_2_value % 24;

		std::vector <short> ud_edges = { FR, FL, BL, BR };

		short rotations;

		for (short i = 0; i != 3; i++) {
			rotations = perm % (i + 2);
			while (rotations != 0) {
				ud_edges = rotate_right(ud_edges, 0, i + 1);
				rotations--;
			}
			perm = perm / (i + 2);
		}

		short n = 3;
		short x;
		edge_perm.fill(-1);

		for (short i = BR; i != -1; i--) {
			x = b_coefficient(i, n);
			if (pos >= x) {
				pos -= x;
			}
			else {
				edge_perm[i] = ud_edges[n];
				n--;
			}

			if (n == -1) { break; }
		}

		for (short i = BR; i != -1; i--) {
			if (edge_perm[i] == -1) {
				edge_perm[i] = 0;
			}
		}
	}

	//This only works in phase 2,
	//as it assumes that the u and d edges are
	//in the u slice and d slice
	unsigned short get_ud_edges() {
		unsigned short ud_edge_value = 0;
		short count;
		for (short i = DB; i != UR; i--) {
			//You ignore UR as its  location
			//is determined by the other 7 u and d edges
			count = 0;
			for (short j = 0; j != i; j++) {
				if (edge_perm[j] > edge_perm[i]) {
					count++;
				}
			}
			ud_edge_value = i * (count + ud_edge_value);
		}

		//This works similarly to the corner permutation
		//value, almost exactly the same actually
		//since you're considering 7 edges here,
		//and 7 corners there

		return ud_edge_value;
	}

	void set_ud_edges(unsigned short ud_edge_value) {
		std::array <short, 7> ud_edge_coord_array{};
		corn_perm.fill(-1);

		for (short i = 2; i != 9; i++) {
			ud_edge_coord_array[i - 2] = ud_edge_value % (i);
			ud_edge_value /= (i);
		}

		std::vector <short> values = { UR, UF, UL, UB, DR, DF, DL, DB };
		std::vector <short> values2 = { 7, 6, 5, 4, 3, 2, 1, 0 };

		for (short i = 6; i != -1; i--) {
			for (short j = 0; j != 8; j++) {
				if (ud_edge_coord_array[i] == values2[j]) {

					edge_perm[i + 1] = values[j];

					values2[j] = -1;

					for (short x = j - 1; x != -1; x--) {
						values2[x]--;
					}
					break;
				}
			}
		}

		for (short i = 0; i != 8; i++) {
			if (values2[i] >= 0) {
				edge_perm[0] = values[i];
				break;
			}
		}
	}

	// ------------------------------------------------
};

