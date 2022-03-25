#include <GL/glut.h>

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


const std::string corn_pos[8] = { "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB" };
const std::string edge_pos[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

cubie cube = cubie();


int main() {
	
	make_twist_table(); make_flip_table(); make_ud_edges_table(); make_corners_table(); make_ud_slice_phase_2_table();


	std::array <cubie, 48> symmetries = gen_symmetries();
	std::array <cubie, 48> inv_symmetries = gen_inv_symmetries(symmetries);

	generate_twist_symmetry(symmetries, inv_symmetries);

	generate_ud_edges_symmetry(symmetries, inv_symmetries);

	generate_flipslices_symmetry_and_classes(symmetries, inv_symmetries);

	generate_corner_symmetry_and_classes(symmetries, inv_symmetries);


	std::cout << "\n\nmove table and symmetry tables done \n\n";


	make_phase_1_pruning_table();
}



//// angle of rotation for the camera direction
//float angle = 0.0f;
//
//// actual vector representing the camera's direction
//float lx = 0.0f, lz = -1.0f;
//
//// XZ position of the camera
//float x = 0.0f, z = 5.0f;
//
//// the key states. These variables will be zero
////when no key is being presses
//float deltaAngle = 0.0f;
//float deltaMove = 0;
//int xOrigin = -1;
//
//void changeSize(int w, int h) {
//
//	// Prevent a divide by zero, when window is too short
//	// (you cant make a window of zero width).
//	if (h == 0)
//		h = 1;
//
//	float ratio = w * 1.0 / h;
//
//	// Use the Projection Matrix
//	glMatrixMode(GL_PROJECTION);
//
//	// Reset Matrix
//	glLoadIdentity();
//
//	// Set the viewport to be the entire window
//	glViewport(0, 0, w, h);
//
//	// Set the correct perspective.
//	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
//
//	// Get Back to the Modelview
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void drawSnowMan() {
//
//	glColor3f(1.0f, 1.0f, 1.0f);
//
//	// Draw Body
//	glTranslatef(0.0f, 0.75f, 0.0f);
//	glutSolidSphere(0.75f, 20, 20);
//
//	// Draw Head
//	glTranslatef(0.0f, 1.0f, 0.0f);
//	glutSolidSphere(0.25f, 20, 20);
//
//	// Draw Eyes
//	glPushMatrix();
//	glColor3f(0.0f, 0.0f, 0.0f);
//	glTranslatef(0.05f, 0.10f, 0.18f);
//	glutSolidSphere(0.05f, 10, 10);
//	glTranslatef(-0.1f, 0.0f, 0.0f);
//	glutSolidSphere(0.05f, 10, 10);
//	glPopMatrix();
//
//	// Draw Nose
//	glColor3f(1.0f, 0.5f, 0.5f);
//	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
//	glutSolidCone(0.08f, 0.5f, 10, 2);
//}
//
//void computePos(float deltaMove) {
//
//	x += deltaMove * lx * 0.1f;
//	z += deltaMove * lz * 0.1f;
//}
//
//void renderScene(void) {
//
//	if (deltaMove)
//		computePos(deltaMove);
//
//	// Clear Color and Depth Buffers
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// Reset transformations
//	glLoadIdentity();
//	// Set the camera
//	gluLookAt(x + lx, 1.0f, z,
//		x, 1.0f, z + lz,
//		0.0f, 1.0f, 0.0f);
//
//	// Draw ground
//
//	glColor3f(0.9f, 0.9f, 0.9f);
//	glBegin(GL_QUADS);
//	glVertex3f(-100.0f, 0.0f, -100.0f);
//	glVertex3f(-100.0f, 0.0f, 100.0f);
//	glVertex3f(100.0f, 0.0f, 100.0f);
//	glVertex3f(100.0f, 0.0f, -100.0f);
//	glEnd();
//
//	// Draw 36 SnowMen
//
//	for (int i = -3; i < 3; i++)
//		for (int j = -3; j < 3; j++) {
//			glPushMatrix();
//			glTranslatef(i * 10.0, 0, j * 10.0);
//			drawSnowMan();
//			glPopMatrix();
//		}
//	glutSwapBuffers();
//}
//
//void processNormalKeys(unsigned char key, int xx, int yy) {
//
//	if (key == 27)
//		exit(0);
//}
//
//void pressKey(int key, int xx, int yy) {
//
//	switch (key) {
//	case GLUT_KEY_UP: deltaMove = 0.5f; break;
//	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
//	}
//}
//
//void releaseKey(int key, int x, int y) {
//
//	switch (key) {
//	case GLUT_KEY_UP:
//	case GLUT_KEY_DOWN: deltaMove = 0; break;
//	}
//}
//
//void mouseMove(int x, int y) {
//
//	// this will only be true when the left button is down
//	if (xOrigin >= 0) {
//
//		// update deltaAngle
//		deltaAngle = (x - xOrigin) * 0.005f;
//
//		// update camera's direction
//		lx = sin(angle + deltaAngle);
//		lz = -cos(angle + deltaAngle);
//	}
//}
//
//void mouseButton(int button, int state, int x, int y) {
//
//	// only start motion if the left button is pressed
//	if (button == GLUT_LEFT_BUTTON) {
//
//		// when the button is released
//		if (state == GLUT_UP) {
//			angle += deltaAngle;
//			xOrigin = -1;
//		}
//		else {// state = GLUT_DOWN
//			xOrigin = x;
//		}
//	}
//}
//
//int main(int argc, char** argv) {
//
//	// init GLUT and create window
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(320, 320);
//	glutCreateWindow("Lighthouse3D - GLUT Tutorial");
//
//	// register callbacks
//	glutDisplayFunc(renderScene);
//	glutReshapeFunc(changeSize);
//	glutIdleFunc(renderScene);
//
//	glutIgnoreKeyRepeat(1);
//	glutKeyboardFunc(processNormalKeys);
//	glutSpecialFunc(pressKey);
//	glutSpecialUpFunc(releaseKey);
//
//	// here are the two new functions
//	glutMouseFunc(mouseButton);
//	glutMotionFunc(mouseMove);
//
//	// OpenGL init
//	glEnable(GL_DEPTH_TEST);
//
//	// enter GLUT event processing cycle
//	glutMainLoop();
//
//	return 1;
//}