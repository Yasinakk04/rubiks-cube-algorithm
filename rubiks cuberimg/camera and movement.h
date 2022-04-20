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

//The below stores the moves in the solution
std::vector <short> optimised_solution;
short m = 0;
//m is the move n=in the vector that's to be done

//The below vector stores moves that have previously been performed
std::vector <short> prev_moves;

bool solve_mode = false;

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

	else if (net == true) {
		drawNet(1, -1, 6);
		centrex = 0.0f; centrey = 0.0f; centrez = 10.0f;
		eyex = 0.0f; eyey = 0.0f; eyez = 11.0f;
	}

	else if (net == false) {
		draw3DCube(	-1,  3,  0, 
					 2,  3,  0, 
					-1,  0,  0,
					-1,  3, -3);
	}

	if (solve_mode == true) {
		drawColourSelection();
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

void pressKey(int key, int xx, int yy) {

	int shift = glutGetModifiers();

	if (key == GLUT_KEY_UP && shift == GLUT_ACTIVE_SHIFT) { centrey = centrey + 0.1f; }
	else if (key == GLUT_KEY_DOWN && shift == GLUT_ACTIVE_SHIFT) { centrey = centrey - 0.1f; }
	else if (key == GLUT_KEY_UP){ deltaMove = 0.5f; }
	else if (key == GLUT_KEY_DOWN) { deltaMove = -0.5f; }
}

void releaseKey(int key, int x, int y) {

	int shift = glutGetModifiers();

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (m < optimised_solution.size()) {
			do_move_on_cube(optimised_solution[m]);
			m++;
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

	if (clock() < CLOCKS_PER_SEC * 0.3f + start || net == true) {

		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && optimised_solution.size() == 0) {
			unsigned char pixel[4];
			glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

			if (!(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0)) {
				unsigned char face = pixel[0] % 247;
				unsigned short facelet_number = pixel[2] % 247;

				if (facelet_number != 4) {
					facelet_numbers[9 * face + facelet_number]++;
					facelet_numbers[9 * face + facelet_number] = facelet_numbers[9 * face + facelet_number] % 6;
				}
			}
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

		std::cout << xPos << "\n";
		std::cout << yPos << "\n";


		if (xPos <= -0.05f && xPos >= -0.65f &&			//This is for the virtual cube
			yPos <= -0.3f && yPos >= -0.6f) {
			menu = false;
			net = false;

			centrex = 0.5f; centrey = 1.5f; centrez = -1.5f;
			eyex = 6.5f; eyey = 5.0f; eyez = 4.5f;
			xangle = -4.0f; yangle = -1.0f;
		}

		if (xPos >= 0.05f && xPos <= 0.65f &&			//This is for the solver
			yPos <= -0.3f && yPos >= -0.6f) {
			menu = false;
			net = true;
			solve_mode = true;
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

void processNormalKeys(unsigned char key, int xx, int yy) {
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

	else if (key == 32) {					//press space to swap
		net = !net;

		centrex = 0.5f; centrey = 1.5f; centrez = -1.5f;
		eyex = 6.5f; eyey = 5.0f; eyez = 4.5f;
		xangle = -4.0f; yangle = -1.0f;
	}

	else if (key == 'u' ||
		key == 'r' ||
		key == 'f' ||
		key == 'd' ||
		key == 'l' ||
		key == 'b') {


		/*if (optimised_solution.size() > 0) {
			std::cout << "\n\nSolution must be recalculated\n\n";
			m = 0;
			optimised_solution.clear();
		}*/

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
		do_move_on_cube(m);

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
							D, R, U, F, B, R, F, F, B};
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

		default:
			for (char i = 0; i != 54; i++) {
				colour_perm[i] = facelet_numbers[i];
			}
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
}