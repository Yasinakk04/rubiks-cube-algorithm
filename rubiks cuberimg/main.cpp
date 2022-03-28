
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
#include <math.h>

#include "enums.h"
#include "cubie.h"
#include "facelets.h"
#include "constants.h"
#include "miscellaneous functions.h"
#include "coord.h"
#include "symmetries.h"
#include "moves.h"
#include "pruning.h"

#include "make facelets.h"
#include "camera and movement.h"

const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

cubie cube = cubie();


//int main() {
//	
//	make_twist_table(); make_flip_table(); make_ud_edges_table(); make_corners_table(); make_ud_slice_phase_2_table();
//
//
//	std::array <cubie, 48> symmetries = gen_symmetries();
//	std::array <cubie, 48> inv_symmetries = gen_inv_symmetries(symmetries);
//
//	generate_twist_symmetry(symmetries, inv_symmetries);
//
//	generate_ud_edges_symmetry(symmetries, inv_symmetries);
//
//	generate_flipslices_symmetry_and_classes(symmetries, inv_symmetries);
//
//	generate_corner_symmetry_and_classes(symmetries, inv_symmetries);
//
//
//	std::cout << "\n\nmove table and symmetry tables done \n\n";
//
//
//	std::cout << "this is for the second pruning table:\n\n";
//
//	make_phase_2_pruning_table();
//}



void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, -5.0f, z,
		x + lx, -5.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawNet(1, 0 ,0);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMouseFunc(checkColour);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}