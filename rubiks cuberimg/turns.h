#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "moves.h"
#include "cubie.h"
#include "enums.h"
#include "make facelets.h"

bool debug = true;

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

std::vector <short> read_solution() {
	std::vector <short> optimised_solution;
	short m;
	std::string string_solution;

	unsigned short i = 0;
	unsigned short size = solution.size();
	solution.push_back(100);				//This is to prevent an error if it checks an index that is undefined
	solution.push_back(100);				//as to optimise the solution slightly it removes characters repeated more than 4 times
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	solution.push_back(100);
	unsigned short count = 1;
	while (i != solution.size()){
		char move;
		short times = 0;

		switch (solution[i]) {
		case U:
			move = 'U';
			m = U;
			break;
		case R:
			move = 'R';
			m = R;
			break;
		case F:
			move = 'F';
			m = F;
			break; 
		case D:
			move = 'D';
			m = D;
			break;
		case L:
			move = 'L';
			m = L;
			break;
		case B:
			move = 'B';
			m = B;
			break;
		case 100:
			move = ' ';
			break;
		default:
			move = '-';
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
			solution[i + 5] == solution[i + 7]) {			//This is the case where 8 consecutive moves are the same
			i = i + 8;										//doing a move 4 times returns it to its orignal state so it removes thsi
		}

		else if (solution[i] == solution[i + 1] &&			//this is the case where a move is repeated 4 times
			solution[i + 2] == solution[i + 3] &&			//which it also removes
			solution[i + 3] == solution[i]) {
			i = i + 4;
		}

		else if (solution[i] == solution[i + 2] &&				//This is where a move is repeated 3 times
			solution[i] == solution[i + 1]) {					//here it outputs the number of times and the move to the console
			std::cout << count << ") " << move << "'" << "\n";
			i = i + 3;
			count++;
			times = 3;			
		}

		else if (solution[i] == solution[i + 1]) {				//This is the case where a move is repeated twice
			i = i + 2;
			std::cout << count << ") " << move << 2 << "\n";
			count++;
			times = 2;
		}

		else {													//this is the case where a move is not repeated at all
			i = i + 1;
			std::cout << count << ") " << move << "\n";
			count++;
			times = 1;
		}

		for (short j = 0; j != times; j++) {
			optimised_solution.push_back(m);
		}
		string_solution.push_back(move);

		if (times == 2) {
			string_solution.push_back('2'); 
		}

		else if (times == 3) {
			string_solution.push_back(39); //ascii code for ' is 39	https://theasciicode.com.ar/ascii-printable-characters/single-quote-apostrophe-ascii-code-39.html
		}
		string_solution.push_back(' ');
	}
	if (debug == true) {
		std::cout << "\n\n" << string_solution;
	}
	return optimised_solution;
}

void reset_colours() {
	for (short i = 0; i != 54; i++) {		//the coolours of the cube are each defined as values between 0 and 5
		facelet_numbers[i] = i / 9;			//this sets all the colours back to that of a solved cube
	}
}

void do_move_on_cube(short m) {
	unsigned short i = 0;

	std::array <unsigned short, 54> temp_facelet_numbers = {			//This function defines each of the 6 moves in terms of where each facelet
	U, U, U, U, U, U, U, U, U,											//moves to	
	R, R, R, R, R, R, R, R, R,
	F, F, F, F, F, F, F, F, F,
	D, D, D, D, D, D, D, D, D,
	L, L, L, L, L, L, L, L, L,
	B, B, B, B, B, B, B, B, B
	};


	switch (m) {
	case U:
		temp_facelet_numbers = {
				facelet_numbers[6], facelet_numbers[3], facelet_numbers[0],
				facelet_numbers[7], 		U,			facelet_numbers[1],
				facelet_numbers[8], facelet_numbers[5], facelet_numbers[2],


				facelet_numbers[53], facelet_numbers[52], facelet_numbers[51],
				facelet_numbers[12],		R,			  facelet_numbers[14],
				facelet_numbers[15], facelet_numbers[16], facelet_numbers[17],


				facelet_numbers[9], facelet_numbers[10], facelet_numbers[11],
				facelet_numbers[21],		F,	 		 facelet_numbers[23],
				facelet_numbers[24], facelet_numbers[25], facelet_numbers[26],


				facelet_numbers[27], facelet_numbers[28], facelet_numbers[29],
				facelet_numbers[30], 		D,			  facelet_numbers[32],
				facelet_numbers[33], facelet_numbers[34], facelet_numbers[35],


				facelet_numbers[18], facelet_numbers[19], facelet_numbers[20],
				facelet_numbers[39],		L,			  facelet_numbers[41],
				facelet_numbers[42], facelet_numbers[43], facelet_numbers[44],


				facelet_numbers[45], facelet_numbers[46], facelet_numbers[47],
				facelet_numbers[48],		B,			  facelet_numbers[50],
				facelet_numbers[38], facelet_numbers[37], facelet_numbers[36]
		};
		break;

	case R:
		temp_facelet_numbers = {
				facelet_numbers[0], facelet_numbers[1], facelet_numbers[20],
				facelet_numbers[3],			U,			facelet_numbers[23],
				facelet_numbers[6], facelet_numbers[7], facelet_numbers[26],


				facelet_numbers[15], facelet_numbers[12], facelet_numbers[9],
				facelet_numbers[16],		R,			  facelet_numbers[10],
				facelet_numbers[17], facelet_numbers[14], facelet_numbers[11],


				facelet_numbers[18], facelet_numbers[19], facelet_numbers[29],
				facelet_numbers[21],		F,			  facelet_numbers[32],
				facelet_numbers[24], facelet_numbers[25], facelet_numbers[35],


				facelet_numbers[27], facelet_numbers[28], facelet_numbers[47],
				facelet_numbers[30],		D,	   		  facelet_numbers[50],
				facelet_numbers[33], facelet_numbers[34], facelet_numbers[53],


				facelet_numbers[36], facelet_numbers[37], facelet_numbers[38],
				facelet_numbers[39],		L,	 		  facelet_numbers[41],
				facelet_numbers[42], facelet_numbers[43], facelet_numbers[44],


				facelet_numbers[45], facelet_numbers[46], facelet_numbers[2],
				facelet_numbers[48],		B,			  facelet_numbers[5],
				facelet_numbers[51], facelet_numbers[52], facelet_numbers[8]
		};
		break;

	case F:
		temp_facelet_numbers = {
				facelet_numbers[0] , facelet_numbers[1] , facelet_numbers[2],
				facelet_numbers[3] ,		U,			  facelet_numbers[5],
				facelet_numbers[44], facelet_numbers[41], facelet_numbers[38],


				facelet_numbers[6] , facelet_numbers[10], facelet_numbers[11],
				facelet_numbers[7] ,		R,			  facelet_numbers[14],
				facelet_numbers[8] , facelet_numbers[16], facelet_numbers[17],


				facelet_numbers[24], facelet_numbers[21], facelet_numbers[18],
				facelet_numbers[25],		F,			  facelet_numbers[19],
				facelet_numbers[26], facelet_numbers[23], facelet_numbers[20],


				facelet_numbers[15], facelet_numbers[12], facelet_numbers[9],
				facelet_numbers[30],		D,	   		  facelet_numbers[32],
				facelet_numbers[33], facelet_numbers[34], facelet_numbers[35],


				facelet_numbers[36], facelet_numbers[37], facelet_numbers[27],
				facelet_numbers[39],		L,	 		  facelet_numbers[28],
				facelet_numbers[42], facelet_numbers[43], facelet_numbers[29],


				facelet_numbers[45], facelet_numbers[46], facelet_numbers[47],
				facelet_numbers[48],		B,			  facelet_numbers[50],
				facelet_numbers[51], facelet_numbers[52], facelet_numbers[53]
		};
		break;

	case D:
		temp_facelet_numbers = {
				facelet_numbers[0] , facelet_numbers[1] , facelet_numbers[2],
				facelet_numbers[3] ,		U,			  facelet_numbers[5],
				facelet_numbers[6] , facelet_numbers[7] , facelet_numbers[8],


				facelet_numbers[9] , facelet_numbers[10], facelet_numbers[11],
				facelet_numbers[12],		R,			  facelet_numbers[14],
				facelet_numbers[24], facelet_numbers[25], facelet_numbers[26],


				facelet_numbers[18], facelet_numbers[19], facelet_numbers[20],
				facelet_numbers[21],		F,			  facelet_numbers[23],
				facelet_numbers[42], facelet_numbers[43], facelet_numbers[44],


				facelet_numbers[33], facelet_numbers[30], facelet_numbers[27],
				facelet_numbers[34],		D,	   		  facelet_numbers[28],
				facelet_numbers[35], facelet_numbers[32], facelet_numbers[29],


				facelet_numbers[36], facelet_numbers[37], facelet_numbers[38],
				facelet_numbers[39],		L,	 		  facelet_numbers[41],
				facelet_numbers[47], facelet_numbers[46], facelet_numbers[45],


				facelet_numbers[17], facelet_numbers[16], facelet_numbers[15],
				facelet_numbers[48],		B,			  facelet_numbers[50],
				facelet_numbers[51], facelet_numbers[52], facelet_numbers[53]
		};
		break;

	case L:
		temp_facelet_numbers = {
				facelet_numbers[45], facelet_numbers[1] , facelet_numbers[2],
				facelet_numbers[48],		U,			  facelet_numbers[5],
				facelet_numbers[51], facelet_numbers[7] , facelet_numbers[8],


				facelet_numbers[9] , facelet_numbers[10], facelet_numbers[11],
				facelet_numbers[12],		R,			  facelet_numbers[14],
				facelet_numbers[15], facelet_numbers[16], facelet_numbers[17],


				facelet_numbers[0] , facelet_numbers[19], facelet_numbers[20],
				facelet_numbers[3] ,		F,			  facelet_numbers[23],
				facelet_numbers[6] , facelet_numbers[25], facelet_numbers[26],


				facelet_numbers[18], facelet_numbers[28], facelet_numbers[29],
				facelet_numbers[21],		D,	   		  facelet_numbers[32],
				facelet_numbers[24], facelet_numbers[34], facelet_numbers[35],


				facelet_numbers[42], facelet_numbers[39], facelet_numbers[36],
				facelet_numbers[43],		L,	 		  facelet_numbers[37],
				facelet_numbers[44], facelet_numbers[41], facelet_numbers[38],


				facelet_numbers[27], facelet_numbers[46], facelet_numbers[47],
				facelet_numbers[30],		B,			  facelet_numbers[50],
				facelet_numbers[33], facelet_numbers[52], facelet_numbers[53]
		};
		break;

	case B:
		temp_facelet_numbers = {
				facelet_numbers[11], facelet_numbers[14], facelet_numbers[17],
				facelet_numbers[3] ,		U,			  facelet_numbers[5],
				facelet_numbers[6] , facelet_numbers[7] , facelet_numbers[8],


				facelet_numbers[9] , facelet_numbers[10], facelet_numbers[35],
				facelet_numbers[12],		R,			  facelet_numbers[34],
				facelet_numbers[15], facelet_numbers[16], facelet_numbers[33],


				facelet_numbers[18], facelet_numbers[19], facelet_numbers[20],
				facelet_numbers[21],		F,			  facelet_numbers[23],
				facelet_numbers[24], facelet_numbers[25], facelet_numbers[26],


				facelet_numbers[27], facelet_numbers[28], facelet_numbers[29],
				facelet_numbers[30],		D,	   		  facelet_numbers[32],
				facelet_numbers[36], facelet_numbers[39], facelet_numbers[42],


				facelet_numbers[2] , facelet_numbers[37], facelet_numbers[38],
				facelet_numbers[1] ,		L,	 		  facelet_numbers[41],
				facelet_numbers[0] , facelet_numbers[43], facelet_numbers[44],


				facelet_numbers[51], facelet_numbers[48], facelet_numbers[45],
				facelet_numbers[52],		B,			  facelet_numbers[46],
				facelet_numbers[53], facelet_numbers[50], facelet_numbers[47]
		};
		break;

	default:
		for (unsigned char i = 0; i != 54; i++) {
			temp_facelet_numbers[i] = facelet_numbers[i];
		}
		break;
	}

	i++;

	for (unsigned char i = 0; i != 54; i++) {
		facelet_numbers[i] = temp_facelet_numbers[i];
	}
}

void do_move_on_cube(std::vector <short> do_solution) {		//This function allows for a series of moves defined in a vector to be carried out
	unsigned short i = 0;									
														
	std::array <unsigned short, 54> temp_facelet_numbers = {
	U, U, U, U, U, U, U, U, U,
	R, R, R, R, R, R, R, R, R,
	F, F, F, F, F, F, F, F, F,
	D, D, D, D, D, D, D, D, D,
	L, L, L, L, L, L, L, L, L,
	B, B, B, B, B, B, B, B, B
	};

	if (do_solution.size() > 0) {
		do {
			do_move_on_cube(do_solution[i]);
			i++;

		} while (i != do_solution.size());
	}
}


