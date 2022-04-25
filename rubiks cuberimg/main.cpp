
/*
 * GL03Viewport.cpp: Clipping-area and Viewport
 * Implementing reshape to ensure same aspect ratio between the
 * clipping-area and the viewport.
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>

#include "enums.h"
#include "cubie.h"
#include "facelets.h"
#include "constants.h"
//#include "miscellaneous functions.h"
//#include "coord.h"
//#include "symmetries.h"
//#include "moves.h"
#include "turns.h"
//#include "pruning.h"

#include "solver.h"

#include "make facelets.h"
#include "camera and movement.h"

const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

cubie cube = cubie();

int main(int argc, char** argv) {
//
//Controls:
//	Press the following keys to turn the matching face 90 degrees
//		U - White face
//		R - Red face
//		F - Green face
//		D - Yellow face
//		L - Orange face
//		B - Blue face
//
//		Solve :
//	To choose the colours on a face click on the square with the mouse
//		This will cycle through the colours in the order :
//	White, Red, Green, Yellow, Orange, Blue
//		You cannot change the centre colour of any face
//		To output the solution press enter or press solve
//		To have the moves performed on the cube press the right and left arrow keys
//
//		Miscellaneous :
//	To swap between the cube view and net view press space
//		To reset the cube press q or press reset
//		To invert the camera press i or press invert



	std::cout << "\n"
		"Controls:\n\n"
		"Press the following keys to turn the matching face 90 degrees\n"
		"U - White face\n"
		"R - Red face\n"
		"F - Green face\n"
		"D - Yellow face\n"
		"L - Orange face\n"
		"B - Blue face\n\n\n"

		"Solve:\n\n"
		"To choose the colours on a face click on the square with the mouse\n"
		"This will cycle through the colours in the order:\n"
		"White, Red, Green, Yellow, Orange, Blue\n"
		"You cannot change the centre colour of any face\n"
		"To output the solution press enter"
		"To have the moves performed on the cube press the right and left arrow keys\n\n\n"

		"Miscellaneous:\n\n"
		"To swap between the cube view and net view press space\n"
		"To reset the cube press q\n"
		"To invert the camera press i\n"
		"To learn how to solve the Rubik's cube I advise using this site:\n"
		"https://www.wikihow.com/Solve-a-Rubik%27s-Cube-with-the-Layer-by-Layer-Method \n\n"
		"This is also the method used by the program\n"
		
		;

	//https://stackoverflow.com/questions/1135841/c-multiline-string-literal


	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Rubiks cube solver");

	initRendering();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	//uuuglutKeyboardFunc(change_colour_keypress);
	

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();


	return 1;
}