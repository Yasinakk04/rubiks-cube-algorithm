#pragma once


//Some of the code used here was sourced from 
//http://www.lighthouse3d.com/tutorials/glut-tutorial/the-code-so-far-ii/





// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;


void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

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

	drawNet(1, 0, 0);

	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

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
}

void checkColour(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		unsigned char pixel[4];
		glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
		std::cout << "R: " << (int)pixel[0] << std::endl;
		std::cout << "G: " << (int)pixel[1] << std::endl;
		std::cout << "B: " << (int)pixel[2] << std::endl;
		std::cout << std::endl;

		if (!(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0)) {
			unsigned char face = pixel[0] % 247;
			unsigned short facelet = pixel[2] % 247;

			facelets[9 * face + facelet]++;
			facelets[9 * face + facelet] = facelets[9 * face + facelet] % 6;
		}
	}


}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);
}