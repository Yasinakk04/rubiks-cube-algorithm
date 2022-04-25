#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include <ctime>

#include "solver.h"
#include "enums.h"
#include "make facelets.h"
#include "solver.h"
#include "menu.h"

//Some of the code used here was sourced from 
//http://www.lighthouse3d.com/tutorials/glut-tutorial/the-code-so-far-ii/

//this timer records how long the left mouse button is held down
clock_t start = 0;

//This stores the height and width of the window
int height = 0;
int width = 0;

// angle of rotation for the camera direction
float xangle = 0.0f;
float yangle = 0.0f;

// actual vector representing the camera's direction
float up_vec = 1.0f;
// XZ position of the camera
float eyex = 0.0f, eyey = 0.0f, eyez = 13.0f;

// position of where youre looking at
float centrex = 0.0f, centrey = 0.0f, centrez = 10.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngleA = 0.0f;
float deltaAngleB = 0.0f;
float deltaMove = 0;
int oldx = -1;
int oldy = -1;

//This determines if a 3D cube is drawn or the net
bool net = true;

//this determines if you should be on the menu or not
bool menu = true;

//this determines if it should display the instructions
bool instructions = false;



//The below vector stores moves that have previously been performed
std::vector <short> prev_moves;

bool solve_mode = false;

//This tells you if you're colouring the squares with the colours in the bottom right or not
short colouring = -1;

void processNormalKeys(unsigned char key, int xx, int yy);

void renderScene(void) {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(eyex, eyey, eyez,
		centrex, centrey, centrez,
		0.0f, up_vec, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (menu == true) {
		drawMenu();
	}

	else if (instructions == true) {
		drawInstructions();
	}

	else if (net == true) {
		drawNet(1, -1, 6);
		centrex = 0.0f; centrey = 0.0f; centrez = 10.0f;
		eyex = 0.0f; eyey = 0.0f; eyez = 11.0f;
		drawReset();
	}

	else if (net == false) {
		draw3DCube(	-1,  3,  0, 
					 2,  3,  0, 
					-1,  0,  0,
					-1,  3, -3);
		drawReset();
	}

	if (solve_mode == true) {
		drawColourSelection();
		drawSolve();
		drawMoves();
	}

	if (menu == false) {
		drawBack();
	}

	glutSwapBuffers();
}

void changeSize(int w, int h) {
	h = w / 16.0 * 9.0;
	float ratio = w * 1.0 / h;

	h = w / 16.0 * 9.0;
	glutReshapeWindow(w, h); //Return window to my size.
								//https://www.opengl.org/resources/libraries/glut/spec3/node23.html

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	height = h;
	width = w;
}

float mousePosX(int x) {
	return 2.0f * ((float)x - ((float)width / 2.0f)) / (float)width;
}
float mousePosY(int y) {
	return -2.0f * ((float)y - ((float)height / 2.0f)) / (float)height;
}

void releaseKey(int key, int x, int y) {

	int shift = glutGetModifiers();

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (m < optimised_solution.size()) {
			do_move_on_cube(optimised_solution[m]);
			m++;
			std::cout << m << "\n";
		}

		break;

	case GLUT_KEY_LEFT: 
		std::vector <short> last_move;
		if (m - 1 >= 0 && prev_moves.size() == 0) {
			for (unsigned char i = 0; i != 3; i++) {
				last_move.push_back(optimised_solution[m - 1]);
			}
			do_move_on_cube(last_move);
			m--;
		}

		else if (prev_moves.size() > 0) {
			short m = prev_moves.back();
			prev_moves.pop_back();
			do_move_on_cube(m);	do_move_on_cube(m);	do_move_on_cube(m);
		}

		break;
	}
}

void mouseButton(int button, int state, int x, int y) {
	
	if (start == 0) {
		start = clock();
	}

	if (((clock() < CLOCKS_PER_SEC * 0.3f + start) || net == true) && mousePosX(x) < 0.65f && mousePosX(x) > -0.2f && solve_mode == true) {

		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && optimised_solution.size() == 0) {
			unsigned char pixel[4];
			glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

			if (!(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0)) {
				unsigned char face = pixel[0] % 247;
				unsigned short facelet_number = pixel[2] % 247;

				if (facelet_number != 4 && colouring == -1) {
					facelet_numbers[9 * face + facelet_number]++;
					facelet_numbers[9 * face + facelet_number] = facelet_numbers[9 * face + facelet_number] % 6;
				}

				else if (facelet_number != 4 && facelet_numbers[9 * face + facelet_number] != colouring) {
					facelet_numbers[9 * face + facelet_number] = colouring;
				}

				else if (facelet_number != 4 && facelet_numbers[9 * face + facelet_number] == colouring) {
					facelet_numbers[9 * face + facelet_number]++;
					facelet_numbers[9 * face + facelet_number] = facelet_numbers[9 * face + facelet_number] % 6;
					colouring = -1;
				}
			}
		}
	}

	else if (mousePosX(x) > 0.65f) {
		unsigned char pixel[4];
		glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) {
			colouring = U;
		}

		else if (pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0) {
			colouring = R;
		}

		else if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0) {
			colouring = F;
		}

		else if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 0) {
			colouring = D;
		}

		else if (pixel[0] == 255 && pixel[1] == 169 && pixel[2] == 0) {
			colouring = L;
		}

		else if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255) {
			colouring = B;
		}
	}

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON && net == false) {

		// when the button is released
		if (state == GLUT_UP) {
			xangle += deltaAngleA;
			yangle += deltaAngleB;
			oldx = -1;
			oldy = -1;

			start = 0;

			if (debug == true) {
				std::cout << "eyex is: " << eyex << "\n";
				std::cout << "eyey is: " << eyey << "\n";
				std::cout << "eyez is: " << eyez << "\n\n";

				std::cout << "xangle is: " << xangle << "\n";
				std::cout << "yangle is: " << yangle + deltaAngleB << "\n\n\n";
			}
		}

		else {// state = GLUT_DOWN
			oldx = x;
			oldy = y;
		}
	}

	if (button == GLUT_LEFT_BUTTON && menu == true && state == GLUT_UP) {
		float xPos = mousePosX(x);
		float yPos = mousePosY(y);

		if (xPos <= -0.05f && xPos >= -0.65f &&			//This is for the virtual cube
			yPos <= -0.3f && yPos >= -0.6f) {
			menu = false;
			net = false;

			colouring = -1;

			centrex = 0.5f; centrey = 1.5f; centrez = -1.5f;
			eyex = 6.5f; eyey = 5.0f; eyez = 4.5f;
			xangle = -4.0f; yangle = -1.0f;
		}

		else if (xPos >= 0.05f && xPos <= 0.65f &&			//This is for the solver
			yPos <= -0.3f && yPos >= -0.6f) {
			menu = false;
			net = true;
			solve_mode = true;

			colouring = -1;
		}

		else if (xPos >= 0.8f && xPos <= 0.95f &&			//This is for the instructions
			yPos <= -0.7f && yPos >= -0.95f) {
			menu = false;
			instructions = true;
			net = false;
			solve_mode = false;
		}
	}
	
	if (button == GLUT_LEFT_BUTTON && menu == false && state == GLUT_UP) {  
		float xPos = mousePosX(x);
		float yPos = mousePosY(y);
		
		if (xPos <= -0.7f && xPos >= -0.9f &&	//This is for returning to the menu
			yPos <= -0.55f && yPos >= -0.9f) {
			menu = true;
			colouring = -1;
			solve_mode = false;
			instructions = false;

			reset_colours();
			m = 0;
			optimised_solution.clear();
			prev_moves.clear();
			up_vec = 1.0f;
		}

		else if (xPos <= 0.95f && xPos >= 0.7f &&	//This is for resetting the cube
			yPos <= -0.2f && yPos >= -0.35f) {
			reset_colours();
			m = 0;
			optimised_solution.clear();
			prev_moves.clear();
			up_vec = 1.0f;
		}

		else if (xPos <= 0.95f && xPos >= 0.7f &&	//This is for solvng the cube
			yPos <= 0.0f && yPos >= -0.15f &&
			solve_mode == true) {
			std::string facelet_rep;
			for (unsigned short i = 0; i != 54; i++) {
				switch (facelet_numbers[i]) {
				case U:
					facelet_rep.push_back('U');
					break;
				case R:
					facelet_rep.push_back('R');
					break;
				case F:
					facelet_rep.push_back('F');
					break;
				case D:
					facelet_rep.push_back('D');
					break;
				case L:
					facelet_rep.push_back('L');
					break;
				case B:
					facelet_rep.push_back('B');
					break;
				default:
					break;
				}
			}

			m = 0;
			optimised_solution.clear();
			prev_moves.clear();
			optimised_solution = solve(facelet_rep);

			if (optimised_solution[0] == -1) { optimised_solution.clear(); }

			if (debug == true) {
				do_move_on_cube(optimised_solution);
				m = optimised_solution.size();
			}
		}
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if ((oldx >= 0 || oldy >= 0) && net == false) {

		// update deltaAngle
		deltaAngleA = (x - oldx) * 0.01f;
		deltaAngleB = (y - oldy) * 0.01f;


		// update camera's direction
		if (up_vec == 1.0f) {
			eyex = 0.5f - 10 * sin(xangle + deltaAngleA) * sin(yangle + deltaAngleB);
		}

		else if (up_vec == -1.0f) {
			eyex = 0.5f + 10 * sin(xangle + deltaAngleA) * sin(yangle + deltaAngleB);
		}

		eyey = 1.5f + 10 * cos(yangle + deltaAngleB);
		eyez = -1.5f + 10 * cos(xangle + deltaAngleA) * sin(yangle + deltaAngleB);
	}
	//Equation for polar coordinates of a sphere below
	//https://www.sciencedirect.com/topics/computer-science/spherical-polar-coordinate
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (menu == false) {

		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			key = tolower(key);
		}

		if (key == 'v') {
			if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
				debug = true;
				std::cout << "DEBUG SCTIVATE\n\n";
			}
		}

		else  if (key == 27) {
			exit(0);
		}

		else if (key == 13) {			//press enter to solve
		std::string facelet_rep;
		for (unsigned short i = 0; i != 54; i++) {	//This converts the permutation to the facelet representation
			switch (facelet_numbers[i]) {
			case U:
				facelet_rep.push_back('U');
				break;
			case R:
				facelet_rep.push_back('R');
				break;
			case F:
				facelet_rep.push_back('F');
				break;
			case D:
				facelet_rep.push_back('D');
				break;
			case L:
				facelet_rep.push_back('L');
				break;
			case B:
				facelet_rep.push_back('B');
				break;
			default:
				break;
			}
		}

		m = 0;
		optimised_solution.clear();
		prev_moves.clear();
		optimised_solution = solve(facelet_rep);

		if (optimised_solution[0] == -1) { optimised_solution.clear(); }

		if (debug == true) {
			do_move_on_cube(optimised_solution);
			m = optimised_solution.size();
			std::cout << optimised_solution.size() << "\n";
		}
	}

		else if (key == 32) {					//press space to swap
		net = !net;

		centrex = 0.5f; centrey = 1.5f; centrez = -1.5f;
		eyex = 6.5f; eyey = 5.0f; eyez = 4.5f;
		xangle = -4.0f; yangle = -1.0f;
	}

		else if (	key == 'u' ||
					key == 'r' ||
					key == 'f' ||
					key == 'd' ||
					key == 'l' ||
					key == 'b' ) {
			key = tolower(key);
			short m;
			switch (key) {
			case 'u':
				m = U;
				break;

			case 'r':
				m = R;
				break;

			case 'f':
				m = F;
				break;

			case 'd':
				m = D;
				break;

			case 'l':
				m = L;
				break;

			case 'b':
				m = B;
				break;

			default:
				m = -1;
				break;
			}

			int shift = glutGetModifiers();		//if shift is pressed it does U', R', F'...
												//https://www.opengl.org/resources/libraries/glut/spec3/node73.html

			if (shift == GLUT_ACTIVE_SHIFT) {
				do_move_on_cube(m);
				do_move_on_cube(m);
				do_move_on_cube(m);
			}

			else {
				do_move_on_cube(m);
			}

			if (m != -1) {
				prev_moves.push_back(m);
			}
		}

		else if (key == 'Z') {		//output the facelet colours
		std::cout << "\n";
		for (unsigned short i = 0; i != 54; i++) {
			switch (facelet_numbers[i]) {
			case U:
				std::cout << "U, ";
				break;
			case R:
				std::cout << "R, ";
				break;
			case F:
				std::cout << "F, ";
				break;
			case D:
				std::cout << "D, ";
				break;
			case L:
				std::cout << "L, ";
				break;
			case B:
				std::cout << "B, ";
				break;
			default:
				break;
			}

			if ((i + 1) % 9 == 0 && i > 0) {
				std::cout << "\n";
			}
		}

		std::cout << "\n\n";
	}

		else if (key == 'z') {
		std::cout << "enter the cube number: ";
		short n;
		std::cin >> n;

		std::array <short, 54> colour_perm{};
		switch (n) {
		case 1:
			colour_perm = { U, L, L, D, U, U, D, B, D,
							B, R, U, U, R, F, R, L, L,
							R, R, L, F, F, L, L, B, B,
							F, U, U, B, D, B, R, D, F,
							R, L, B, U, L, D, F, D, D,
							D, R, U, F, B, R, F, F, B };
			break;

		case 2:
			colour_perm = { B, L, F, U, U, R, F, F, R,
							B, B, R, U, R, R, L, F, D,
							D, L, D, U, F, F, U, B, U,
							F, D, B, F, D, D, B, L, R,
							R, L, L, R, L, B, D, R, L,
							L, D, F, D, B, U, U, B, U };

			break;

		case 3:
			colour_perm = { D, F, D, R, U, D, U, U, F,
							D, L, R, L, R, F, U, F, F,
							L, L, L, R, F, B, L, U, L,
							D, B, F, B, D, L, R, R, R,
							R, D, B, F, L, U, B, D, B,
							U, B, U, U, B, D, B, R, F };
			break;

		case 4:
			colour_perm = { L, B, R, R, U, D, U, U, D,
							L, L, D, F, R, L, F, U, F,
							F, B, F, R, F, D, R, B, D,
							U, D, R, R, D, F, U, L, R,
							D, B, L, U, L, F, B, D, B,
							L, U, U, R, B, F, B, L, B };
			break;

		case 5:
			colour_perm = { B, U, F, F, U, R, B, F, L,
							F, B, R, R, R, U, L, L, U,
							R, L, D, D, F, D, R, B, U,
							D, L, B, R, D, D, L, D, L,
							D, R, U, F, L, B, B, U, F,
							D, F, F, U, B, B, R, L, U };
			break;

		case 6:
			colour_perm = { F, F, B, F, U, L, R, F, D,
							L, D, R, U, R, U, F, R, L,
							D, R, F, R, F, B, B, B, U,
							L, R, L, L, D, D, R, L, U,
							U, L, F, B, L, U, B, U, D,
							U, B, B, D, B, F, R, D, D };
			break;

		case 7:
			colour_perm = { F, F, B, F, U, L, R, F, D,
							L, D, R, U, R, U, F, R, L,
							D, R, F, R, F, B, B, B, U,
							L, R, L, L, D, D, R, L, U,
							U, L, F, B, L, U, B, U, D,
							U, B, B, D, B, F, R, D, D };
			break;

		case 8:
			colour_perm = { B, F, B, D, U, F, R, F, F,
							L, D, R, D, R, R, R, U, L,
							D, R, U, B, F, R, B, F, U,
							L, L, F, L, D, B, F, U, U,
							R, B, F, L, L, R, L, D, D,
							D, L, B, B, B, U, U, U, D };
			break;

		case 9:
			colour_perm = { L, D, R, R, U, F, L, R, B,
							R, D, D, L, R, B, D, B, F,
							B, U, U, R, F, D, R, B, L,
							D, L, B, U, D, R, F, L, L,
							U, D, U, U, L, F, R, L, F,
							U, F, D, F, B, U, F, B, B };
			break;

		case 10:
			colour_perm = { U, D, D, L, U, B, U, B, R,
							U, D, B, U, R, D, U, L, L,
							L, R, B, F, F, B, L, R, L,
							F, U, F, R, D, B, D, F, B,
							R, F, B, L, L, R, R, D, D,
							F, U, D, U, B, F, F, L, R };
			break;

		case 11:
			colour_perm = { D, D, D, L, U, F, B, L, R,
							B, L, F, D, R, L, L, F, R,
							R, B, D, B, F, F, D, R, U,
							B, F, B, R, D, U, F, R, U,
							F, D, U, R, L, U, U, D, L,
							L, U, F, B, B, U, R, B, L };
			break;

		case 12:
			colour_perm = { L, B, L, F, U, F, F, B, L,
							F, R, F, U, R, D, U, D, B,
							R, U, D, L, F, R, L, F, R,
							D, U, B, L, D, B, F, L, R,
							B, D, D, L, L, B, R, D, B,
							U, U, D, F, B, R, U, R, U };
			break;

		case 13:
			colour_perm = { L, R, F, B, U, U, F, R, B,
							L, R, R, U, R, B, F, L, F,
							D, F, D, F, F, L, D, B, U,
							R, L, L, B, D, D, U, F, D,
							B, D, L, F, L, L, R, U, B,
							B, D, R, U, B, R, U, D, U };
			break;

		case 14:
			colour_perm = { B, L, F, R, U, D, F, F, B,
							D, B, L, B, R, U, B, D, L,
							R, R, R, U, F, L, U, L, L,
							B, F, U, R, D, F, R, L, F,
							L, D, D, U, L, R, U, B, R,
							F, D, U, F, B, B, D, U, D };

			break;

		case 15:
			colour_perm = { L, B, U, R, U, U, U, F, F,
							R, L, B, L, R, U, D, F, R,
							F, U, D, B, F, F, B, L, L,
							R, D, B, R, D, D, R, F, D,
							F, B, L, D, L, L, U, U, U,
							F, R, B, R, B, B, D, D, L };
			break;

		case 16:
			colour_perm = { D, B, B, D, U, F, R, D, F,
							U, L, U, R, R, F, D, B, U,
							B, F, R, B, F, U, L, D, R,
							U, R, F, R, D, L, L, L, B,
							L, B, D, U, L, U, B, F, F,
							D, D, L, L, B, U, F, R, R };
			break;

		case 17:
			colour_perm = { R, L, F, F, U, B, U, D, B,
							U, D, L, R, R, R, B, B, R,
							F, F, L, U, F, D, U, D, R,
							B, L, D, R, D, U, L, L, F,
							F, U, L, R, L, L, B, B, R,
							D, B, D, F, B, U, U, F, D };
			break;

		case 18:
			colour_perm = { B, U, F, U, U, U, U, F, U,
							B, L, D, F, R, L, D, B, L,
							F, R, R, D, F, D, R, B, F,
							F, R, L, L, D, U, B, D, B,
							U, R, L, L, L, R, R, B, U,
							D, B, D, D, B, F, L, F, R };
			break;

		case 19:
			colour_perm = { U, B, B, L, U, R, L, D, B,
							U, U, D, B, R, R, U, F, D,
							F, F, L, U, F, D, D, B, L,
							R, U, F, D, D, L, R, B, R,
							B, D, D, U, L, F, U, R, B,
							F, L, F, L, B, F, R, R, L };
			break;

		case 20:
			colour_perm = { D, B, F, F, U, L, B, L, U,
							R, U, U, D, R, B, R, R, L,
							L, F, F, R, F, B, R, F, F,
							U, R, D, D, D, B, L, D, U,
							R, D, D, F, L, U, D, L, B,
							F, R, B, U, B, U, B, L, L };
			break;

		case 21:
			colour_perm = { F, B, D, F, U, L, D, R, R,
							U, F, F, F, R, L, B, D, R,
							F, D, B, U, F, U, L, B, R,
							D, R, D, L, D, B, U, R, U,
							L, D, R, L, L, R, B, B, B,
							L, F, F, D, B, U, U, U, L };
			break;

		case 22:
			colour_perm = { L, L, F, U, U, B, B, B, R,
							U, U, U, D, R, D, R, D, F,
							L, R, B, R, F, B, U, L, F,
							L, F, D, L, D, R, B, F, R,
							F, L, D, R, L, U, R, B, B,
							D, U, U, F, B, F, D, D, L };
			break;

		case 23:
			colour_perm = { F, F, B, L, U, U, B, R, L,
							B, B, R, L, R, U, B, B, U,
							R, D, U, R, F, F, L, U, D,
							U, R, L, U, D, L, D, D, F,
							R, D, U, F, L, B, F, L, F,
							L, B, R, D, B, F, D, R, D };
			break;

		case 24:
			colour_perm = { U, L, F, U, U, R, L, R, R,
							B, B, U, D, R, U, F, D, F,
							D, U, D, F, F, L, D, F, L,
							F, U, D, F, D, B, U, R, R,
							B, B, B, R, L, L, B, D, R,
							L, D, U, F, B, L, R, B, L };
			break;

		case 25:
			colour_perm = { U, B, D, F, U, D, D, B, D,
							F, B, L, D, R, R, B, F, B,
							R, U, R, R, F, L, F, L, L,
							D, U, U, D, D, U, U, L, U,
							R, L, B, R, L, F, L, F, L,
							F, B, R, U, B, D, F, R, B };
			break;

		case 26:
			colour_perm = { D, R, F, B, U, D, U, D, U,
							R, F, D, L, R, U, U, D, B,
							F, R, F, F, F, B, U, F, B,
							B, R, L, U, D, L, F, L, R,
							B, D, L, U, L, U, L, L, R,
							D, F, D, B, B, R, L, B, R };
			

		default:
			for (char i = 0; i != 54; i++) {
				colour_perm[i] = facelet_numbers[i];
			}
			break;
		}

		set_facelet_numbers(colour_perm);
	}

		else if (key == 'q') {
		reset_colours();
		m = 0;
		optimised_solution.clear();
		prev_moves.clear();
	}

		else if (key == 'i' && net == false) {
			up_vec = -up_vec;
		}

		else if ((key == 'U' ||
			key == 'R' ||
			key == 'F' ||
			key == 'D' ||
			key == 'L' ||
			key == 'B') && glutGetModifiers() != GLUT_ACTIVE_SHIFT) {

			std::cout << "YO";

			unsigned char pixel[4];
			glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

			if (!(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) && mousePosX(x) < 0.65f && mousePosX(x) > -0.2f) {
				unsigned char face = pixel[0] % 247;
				unsigned short facelet_number = pixel[2] % 247;

				short colour_key = -1;

				switch (key) {
				case 'U':
					colour_key = U;
					break;
				case 'R':
					colour_key = R;
					break;
				case 'F':
					colour_key = F;
					break;
				case 'D':
					colour_key = D;
					break;
				case 'L':
					colour_key = L;
					break;
				case 'B':
					colour_key = B;
					break;
				default:

					std::cout << "error\n";
					break;
				}

				if (facelet_number != 4 && colour_key != -1) {
					facelet_numbers[9 * face + facelet_number] = colour_key;
				}
			}
		}

		else if (key == 's' && solve_mode == false) {
			for (short i = 0; i != 30; i++) {			//this is for 30 moves
				short m = rand() % 7;					//for each of the 6 different moves
				short times = rand() % 3;			//a move can only be applied a max of 3 times 
													//https://www.cplusplus.com/reference/cstdlib/rand/

				for (short t = 0; t != times; t++) {
					do_move_on_cube(m);					
				}
			}
		}

	}
}

void change_colour_keypress(unsigned char key, int x, int y) {
	if ((key == 'U' ||
		key == 'R' ||
		key == 'F' ||
		key == 'D' ||
		key == 'L' ||
		key == 'B') && glutGetModifiers() != GLUT_ACTIVE_SHIFT){	//This ensures that anticlockwise turns only occur if caps lock is pressed, not shift

		std::cout << "YO";

		unsigned char pixel[4];
		glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		if (!(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) && mousePosX(x) < 0.65f && mousePosX(x) > -0.2f) {
			unsigned char face = pixel[0] % 247;
			unsigned short facelet_number = pixel[2] % 247;

			short colour_key = -1;

			switch (key) {
			case 'U':
				colour_key = U;
				break;
			case 'R':
				colour_key = R;
				break;
			case 'F':
				colour_key = F;
				break;
			case 'D':
				colour_key = D;
				break;
			case 'L':
				colour_key = L;
				break;
			case 'B':
				colour_key = B;
				break;
			default:

				std::cout << "error\n";
				break;
			}

			if (facelet_number != 4 && colour_key != -1) {
				facelet_numbers[9 * face + facelet_number] = colour_key;
			}
		}
	}	
}

