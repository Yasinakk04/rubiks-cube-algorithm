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

void drawMenu() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	glColor3ub(255, 255, 255);


	glEnable(GL_TEXTURE_2D);

	//Bottom

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glBegin(GL_QUADS);
	glVertex2f(-0.7f, 0.2f);
	glVertex2f(0.7f, 0.2f);
	glVertex2f(0.7f, 0.6f);
	glVertex2f(-0.7f, 0.6f);
		

	initRendering("hello.bmp");
	glBindTexture(GL_TEXTURE_2D, _textureId);

						//This displays the start square
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, -0.6f);
	glVertex2f(-0.3f, -0.6f);
	glEnd();

	glDisable(GL_TEXTURE_2D);


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