#pragma once
#include <iostream>
#include <vector>

#include "moves.h"
#include "cubie.h"
#include "enums.h"


std::vector <short> solution;

void cubie::doU(int times) {
	for (int i = 0; i != times; i++) {
		multiply(U_turn);
		solution.push_back(U);
	}
}

void cubie::doR(int times) {
	for (int i = 0; i != times; i++) {
		multiply(R_turn);
		solution.push_back(R);
	}
}

void cubie::doF(int times) {
	for (int i = 0; i != times; i++) {
		multiply(F_turn);
		solution.push_back(F);
	}
}

void cubie::doD(int times) {
	for (int i = 0; i != times; i++) {
		multiply(D_turn);
		solution.push_back(D);
	}
}

void cubie::doL(int times) {
	for (int i = 0; i != times; i++) {
		multiply(L_turn);
		solution.push_back(L);
	}
}

void cubie::doB(int times) {
	for (int i = 0; i != times; i++) {
		multiply(B_turn);
		solution.push_back(B);
	}
}

void read_solution() {
	unsigned short i = 0;
	unsigned short size = solution.size();
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	unsigned short count = 1;
	while (i != solution.size()){
		const char* x;

		switch (solution[i]) {
		case U:
			x = "U";
			break;
		case R:
			x = "R";
			break;
		case F:
			x = "F";
			break; 
		case D:
			x = "D";
			break;
		case L:
			x = "L";
			break;
		case B:
			x = "B";
			break;
		case 100:
			x = "";
			break;
		default:
			x = "fail";
			break;
		}

		if (solution[i] == 100) {
			break;
		}

		if (solution[i] == solution[i + 1] &&
			solution[i + 2] == solution[i + 3] &&
			solution[i + 4] == solution[i + 5] &&
			solution[i + 6] == solution[i + 7] &&
			solution[i + 3] == solution[i]		&&
			solution[i + 3] == solution[i + 5] &&
			solution[i + 5] == solution[i + 7]) {
			i = i + 8;
		}


		else if (solution[i] == solution[i + 1] &&
			solution[i + 2] == solution[i + 3] &&
			solution[i + 3] == solution[i]) {
			i = i + 4;
		}

		else if (solution[i] == solution[i + 2] &&
			solution[i] == solution[i + 1]) {
			std::cout << count << ") " << x << 3 << "\n";
			i = i + 3;
			count++;
		}

		else if (solution[i] == solution[i + 1]) {
			i = i + 2;
			std::cout << count << ") " << x << 2 << "\n";
			count++;
		}

		else {
			i = i + 1;
			std::cout << count << ") " << x << "\n";
			count++;
		}

	}

	solution.clear();
}