#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <stdlib.h>

#include "TextureMapper.h"
//#include "TextureMapper.cpp"
#include "GL\glut.h"

GLuint _textureId; //The id of the texture


GLUquadric* quad;

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

void initRendering(const char* f) {

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_LIGHTING);

	//glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);

	quad = gluNewQuadric();

	Image* image = loadBMP(f);

	_textureId = loadTexture(image);

	delete image;
}

void drawButton(float xBL, float yBL, float xTR, float yTR, const char* tex_name) {
	GLuint tex;

	Image* bmp = loadBMP(tex_name);
	tex = loadTexture(bmp);
	delete bmp;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON);

	//This displays the solver mode
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
	drawButton(-0.7f, 0.2f, 0.7f, 0.6f, "TITLE.bmp"); //the title

	drawButton(-0.65f, -0.6f, -0.05f, -0.3f, "virtual cube.bmp"); //This displays the virtual cube mode

	drawButton(0.05f, -0.6f, 0.65f, -0.3f, "solver.bmp"); //This displays the solver mode

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

	drawButton(-0.9f, -0.9f, -0.7f, -0.55f, "back button.bmp");

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

	drawButton(0.7f, -0.35f, 0.95f, -0.2f, "RESET.bmp");
	
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

	drawButton(0.7f, -0.15f, 0.95f, 0.0f, "solve.bmp");

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//Makes the image into a texture, and returns the id of the texture






//GLUquadricObj quad;

//
//
//void drawScene() {
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//	glMatrixMode(GL_MODELVIEW);
//
//	glLoadIdentity();
//
//
//	glTranslatef(0.0f, 1.0f, -16.0f);
//
//
//	glEnable(GL_TEXTURE_2D);
//
//	glBindTexture(GL_TEXTURE_2D, _textureId);
//
//
//	//Bottom
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	gluQuadricTexture(quad, 1);
//
//	gluSphere(quad, 2, 20, 20);
//
//
//	glutSwapBuffers();
//
//}

//int main(int argc, char** argv) {
//
//	glutInit(&argc, argv);
//
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//
//	glutInitWindowSize(800, 800);
//
//
//	glutCreateWindow("Textures-codeincodeblock.blogspot.com");
//
//	initRendering();
//
//
//	glutTimerFunc(25, update, 0);
//
//
//	glutDisplayFunc(drawScene);
//
//
//	glutMainLoop();
//
//	return 0;
//
//}