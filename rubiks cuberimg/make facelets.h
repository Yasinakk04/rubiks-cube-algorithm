#pragma once
#include <string>

#include "enums.h"
#include "GL\glut.h"

int facelet = 0;
unsigned short facelets[54] = { 
	U, U, U, U, U, U, U, U, U,
	R, R, R, R, R, R, R, R, R,
	F, F, F, F, F, F, F, F, F,
	D, D, D, D, D, D, D, D, D,
	L, L, L, L, L, L, L, L, L,
	B, B, B, B, B, B, B, B, B
};

void drawSquare(float x, float y, float side_length) {

	glBegin(GL_TRIANGLES);

	unsigned short colour = facelets[facelet];
	
	switch (colour) {
	case U:
		glColor3ub(247 + (facelet / 9), 255, 247 + (facelet % 9));
		break;
	case R:
		glColor3ub(247 + (facelet / 9), 0, 0 + (facelet % 9));
		break;
	case F:
		glColor3ub(0 + (facelet / 9), 255, 0 + (facelet % 9));
		break;
	case D:
		glColor3ub(247 + (facelet / 9), 255, 0 + (facelet % 9));
		break;
	case L:
		glColor3ub(247 + (facelet / 9), 128, 0 + (facelet % 9));
		break;
	case B:
		glColor3ub(0 + (facelet / 9), 0, 247 + (facelet % 9));
		break;
	}

	facelet++;
	facelet = facelet % 54;

	glVertex3f(x, y, -5.0);
	glVertex3f(x + side_length, y, -5.0);
	glVertex3f(x, y - side_length, -5.0);

	glVertex3f(x + side_length, y - side_length, -5.0);
	glVertex3f(x + side_length, y, -5.0);
	glVertex3f(x, y - side_length, -5.0);
	glEnd();
}

void draw9Squares(float side_length, float x, float y) {

	glColor3f(1.0, 1.0, 1.0);
	for (unsigned char i = 0; i != 3; i++) {
		for (unsigned char j = 0; j != 3; j++) {
			drawSquare(x + j * side_length, y - i * side_length, side_length);
		}
	}

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (unsigned char i = 0; i != 4; i++) {
		//Vertical lines
		glVertex3f(x + i * side_length, y - (3 * side_length), -4.99);
		glVertex3f(x + i * side_length, y, -4.99);
		glVertex3f(x + i * side_length + (side_length / 10), y - (3 * side_length), -4.99);

		glVertex3f(x + i * side_length + (side_length / 10), y, -4.99);
		glVertex3f(x + i * side_length, y - (3 * side_length), -4.99);
		glVertex3f(x + i * side_length, y, -4.99);

		//Horizontal lines
		glVertex3f(x, y - i * side_length, -4.99);
		glVertex3f(x, y - i * side_length + (side_length / 10), -4.99);
		glVertex3f(x + 3 * side_length, y - i * side_length, -4.99);

		glVertex3f(x + 3 * side_length, y -  i * side_length + (side_length / 10), -4.99);
		glVertex3f(x + 0, y -  i * side_length + (side_length / 10), -4.99);
		glVertex3f(x + 3 * side_length, y - i * side_length, -4.99);
	}
	glEnd();
}

void drawNet(float side_length, float x, float y) {
	//U face
	draw9Squares(side_length, x, y);

	//R face
	draw9Squares(side_length, x + (3 * side_length), y - (3 * side_length));

	//F face
	draw9Squares(side_length, x, y - (3 * side_length));

	//D face
	draw9Squares(side_length, x, y - 2 * (3 * side_length));

	//L face
	draw9Squares(side_length, x - (3 * side_length), y - (3 * side_length));

	//B face
	draw9Squares(side_length, x, y - 3 * (3 * side_length));
}



void drawSquare3D(float xTL, float yTL, float zTL,		//TL is top left
					float xBR, float yBR, float zBR,		//BR is bottom right
					float xBL, float yBL, float zBL) {
	glBegin(GL_TRIANGLES);

	unsigned short colour = facelets[facelet];

	switch (colour) {
	case U:
		glColor3ub(247 + (facelet / 9), 255, 247 + (facelet % 9));
		break;
	case R:
		glColor3ub(247 + (facelet / 9), 0, 0 + (facelet % 9));
		break;
	case F:
		glColor3ub(0 + (facelet / 9), 255, 0 + (facelet % 9));
		break;
	case D:
		glColor3ub(247 + (facelet / 9), 255, 0 + (facelet % 9));
		break;
	case L:
		glColor3ub(247 + (facelet / 9), 128, 0 + (facelet % 9));
		break;
	case B:
		glColor3ub(0 + (facelet / 9), 0, 247 + (facelet % 9));
		break;
	}

	facelet++;
	facelet = facelet % 54;

	glVertex3f(xTL, yTL, zTL);
	glVertex3f(xBR, yBR, zBR);
	glVertex3f(xBL,  yBL,  zBL);

	glVertex3f(xTL, yTL, zTL);
	glVertex3f(xBR, yBR, zBR);
	glVertex3f(xTL + xBR - xBL, yTL + yBR - yBL, zTL + zBR - zBL);
	glEnd();
}
//
////U is white
////R is red
////F is green
////D is yellow
////L is orange
////B is blue