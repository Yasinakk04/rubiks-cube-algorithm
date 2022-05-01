#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "TextureMapper.h"
#include "GL\glut.h"

//The below stores the moves in the solution
std::vector <short> optimised_solution;
short m = 0;
//m is the move in the vector that's to be done

GLuint _textureId; //The id of the texture

GLUquadric* quad;

GLuint U_tex;
GLuint R_tex;
GLuint F_tex;
GLuint D_tex;
GLuint L_tex;
GLuint B_tex;
GLuint back_button_tex;
GLuint instructions_tex;
GLuint question_mark_tex;
GLuint reset_tex;
GLuint solution_tex;
GLuint solve_tex;
GLuint title_tex;
GLuint solver_tex;
GLuint virtual_cube_tex;

GLuint loadTexture(Image* image) {

	GLuint textureId;

	glGenTextures(1, &textureId); //Make room for our texture

	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit

	//Map the image to the texture

	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D

		0,                            //0 for now

		GL_RGB,                       //Format OpenGL uses for image

		image->width, image->height,  //Width and height

		0,                            //The border of the image

		GL_RGB, //GL_RGB, because pixels are stored in RGB format

		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored

						  //as unsigned numbers

		image->pixels);               //The actual pixel data

	return textureId; //Returns the id of the texture

}

void initRendering() {

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);

	quad = gluNewQuadric();

	Image* image = loadBMP("U.bmp");
	U_tex = loadTexture(image);
	delete image;

	image = loadBMP("R.bmp");
	R_tex = loadTexture(image);
	delete image;

	image = loadBMP("F.bmp");
	F_tex = loadTexture(image);
	delete image;

	image = loadBMP("D.bmp");
	D_tex = loadTexture(image);
	delete image;

	image = loadBMP("L.bmp");
	L_tex = loadTexture(image);
	delete image;

	image = loadBMP("B.bmp");
	B_tex = loadTexture(image);
	delete image;

	image = loadBMP("back button.bmp");
	back_button_tex = loadTexture(image);
	delete image;

	image = loadBMP("instructions.bmp");
	instructions_tex = loadTexture(image);
	delete image;

	image = loadBMP("question mark.bmp");
	question_mark_tex = loadTexture(image);
	delete image;

	image = loadBMP("RESET.bmp");
	reset_tex = loadTexture(image);
	delete image;

	image = loadBMP("SOLUTION.bmp");
	solution_tex = loadTexture(image);
	delete image;

	image = loadBMP("solve.bmp");
	solve_tex = loadTexture(image);
	delete image;

	image = loadBMP("solver.bmp");
	solver_tex = loadTexture(image);
	delete image;

	image = loadBMP("TITLE.bmp");
	title_tex = loadTexture(image);
	delete image;

	image = loadBMP("virtual cube.bmp");
	virtual_cube_tex = loadTexture(image);
	delete image;
}

void drawButton(float xBL, float yBL, float xTR, float yTR, GLuint tex) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0); glVertex2f(xBL, yBL);
	glTexCoord2f(1.0, 0.0); glVertex2f(xTR, yBL);
	glTexCoord2f(1.0, 1.0); glVertex2f(xTR, yTR);
	glTexCoord2f(0.0, 1.0); glVertex2f(xBL, yTR);

	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void drawMenu() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	drawButton(-0.7f, 0.2f, 0.7f, 0.6f, title_tex); //the title

	drawButton(-0.65f, -0.6f, -0.05f, -0.3f, virtual_cube_tex); //This displays the virtual cube mode

	drawButton(0.05f, -0.6f, 0.65f, -0.3f, solver_tex); //This displays the solver mode

	drawButton(0.8f, -0.95f, 0.95f, -0.7f, question_mark_tex);  //click this to view the instructions

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void drawColourSelection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);


	glBegin(GL_QUADS);


	glColor3ub(255, 255, 255);	//U - White
	glVertex2f(0.8f, -0.4f);
	glVertex2f(0.7f, -0.4f);
	glVertex2f(0.7f, -0.55f);
	glVertex2f(0.8f, -0.55f);

	glColor3ub(255, 0, 0);	//R - Red
	glVertex2f(0.8f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.7f, -0.75f);
	glVertex2f(0.8f, -0.75f);

	
	glColor3ub(0, 255, 0);	//F - Green
	glVertex2f(0.8f, -0.8f);
	glVertex2f(0.7f, -0.8f);
	glVertex2f(0.7f, -0.95f);
	glVertex2f(0.8f, -0.95f);


	glColor3ub(255, 255, 0);	//D - Yellow
	glVertex2f(0.95f, -0.4f);
	glVertex2f(0.85f, -0.4f);
	glVertex2f(0.85f, -0.55f);
	glVertex2f(0.95f, -0.55f);

	glColor3ub(255, 169, 0);	//L - Orange	
	glVertex2f(0.95f, -0.6f);
	glVertex2f(0.85f, -0.6f);
	glVertex2f(0.85f, -0.75f);
	glVertex2f(0.95f, -0.75f);

	glColor3ub(0, 0, 255);	//B - Blue			
	glVertex2f(0.95f, -0.8f);
	glVertex2f(0.85f, -0.8f);
	glVertex2f(0.85f, -0.95f);
	glVertex2f(0.95f, -0.95f);
	
	glEnd();


	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glColor3ub(255, 255, 255);
}

void drawBack() {
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	drawButton(-0.9f, -0.9f, -0.7f, -0.55f, back_button_tex);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void drawReset() {
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	drawButton(0.7f, -0.35f, 0.95f, -0.2f, reset_tex);
	
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void drawSolve() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	drawButton(0.7f, -0.15f, 0.95f, 0.0f, solve_tex);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void drawInstructions() {
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	drawButton(-0.7f, -1.2f, 0.95f, 1.0f, instructions_tex);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void drawMoves() {
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	GLuint tex = 0;

	if (optimised_solution.size() != 0) {
		if (optimised_solution[0] != -1) {
			drawButton(-0.92f, 0.68f, -0.4f, 1.15f, solution_tex);

			if (m >= 1 && m < optimised_solution.size() - 1) {
				for (char i = 0; i != 3; i++) {
					switch (optimised_solution[m + i - 1]) {
					case U:
						tex = U_tex;
						break;
					case R:
						tex = R_tex;
						break;
					case F:
						tex = F_tex;
						break;
					case D:
						tex = D_tex;
						break;
					case L:
						tex = L_tex;
						break;
					case B:
						tex = B_tex;
						break;
					default:
						std::cout << "error";
						break;
					}
					drawButton(-0.98f + i * 0.2f, 0.4f, -0.73f + i * 0.2f, 0.7f, tex);
				}
			}

			else if (m == 0) {
				for (char i = 1; i != 3; i++) {
					switch (optimised_solution[m + i]) {
					case U:
						tex = U_tex;
						break;
					case R:
						tex = R_tex;
						break;
					case F:
						tex = F_tex;
						break;
					case D:
						tex = D_tex;
						break;
					case L:
						tex = L_tex;
						break;
					case B:
						tex = B_tex;
						break;
					default:
						std::cout << "error";
						break;
					}
					drawButton(-0.98f + i * 0.2f, 0.4f, -0.73f + i * 0.2f, 0.7f, tex);
				}
			}

			else if (m >= optimised_solution.size() - 1) {
				for (char i = 0; i != 2; i++){
					switch (optimised_solution[optimised_solution.size() + i - 2]) {
					case U:
						tex = U_tex;
						break;
					case R:
						tex = R_tex;
						break;
					case F:
						tex = F_tex;
						break;
					case D:
						tex = D_tex;
						break;
					case L:
						tex = L_tex;
						break;
					case B:
						tex = B_tex;
						break;
					default:
						std::cout << "error";
						break;
					}
					drawButton(-0.98f + i * 0.2f, 0.4f, -0.73f + i * 0.2f, 0.7f, tex);
				}
			}

			glBegin(GL_QUADS);
			glColor3ub(255, 255, 255);
			
			glVertex2f(-0.7085f, 0.38f);
			glVertex2f(-0.6085f, 0.38f);
			glVertex2f(-0.6085f, 0.39f);
			glVertex2f(-0.7085f, 0.39f);

			glEnd();
		}
	}


	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}