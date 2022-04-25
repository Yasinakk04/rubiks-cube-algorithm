
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
#include "turns.h"

#include "solver.h"

#include "make facelets.h"
#include "camera and movement.h"

const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

cubie cube = cubie();

int main(int argc, char** argv) {
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
	

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();


	return 1;
}