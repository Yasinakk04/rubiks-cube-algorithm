#pragma once
#include <string>

#include "enums.h"
#include "GL\glut.h"

int facelet_number = 0;
unsigned short facelet_numbers[54] = { 
	U, U, U, U, U, U, U, U, U,
	R, R, R, R, R, R, R, R, R,
	F, F, F, F, F, F, F, F, F,
	D, D, D, D, D, D, D, D, D,
	L, L, L, L, L, L, L, L, L,
	B, B, B, B, B, B, B, B, B
};

void drawSquare(float x, float y, float side_length) {

	glBegin(GL_TRIANGLES);

	unsigned short colour = facelet_numbers[facelet_number];
	
	switch (colour) {
	case U:
		glColor3ub(247 + (facelet_number / 9), 255, 247 + (facelet_number % 9));
		break;
	case R:
		glColor3ub(247 + (facelet_number / 9), 0, 0 + (facelet_number % 9));
		break;
	case F:
		glColor3ub(0 + (facelet_number / 9), 255, 0 + (facelet_number % 9));
		break;
	case D:
		glColor3ub(247 + (facelet_number / 9), 255, 0 + (facelet_number % 9));
		break;
	case L:
		glColor3ub(247 + (facelet_number / 9), 128, 0 + (facelet_number % 9));
		break;
	case B:
		glColor3ub(0 + (facelet_number / 9), 0, 247 + (facelet_number % 9));
		break;
	}

	facelet_number++;
	facelet_number = facelet_number % 54;

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

	unsigned short colour = facelet_numbers[facelet_number];

	switch (colour) {
	case U:
		glColor3ub(247 + (facelet_number / 9), 255, 247 + (facelet_number % 9));
		break;
	case R:
		glColor3ub(247 + (facelet_number / 9), 0, 0 + (facelet_number % 9));
		break;
	case F:
		glColor3ub(0 + (facelet_number / 9), 255, 0 + (facelet_number % 9));
		break;
	case D:
		glColor3ub(247 + (facelet_number / 9), 255, 0 + (facelet_number % 9));
		break;
	case L:
		glColor3ub(247 + (facelet_number / 9), 128, 0 + (facelet_number % 9));
		break;
	case B:
		glColor3ub(0 + (facelet_number / 9), 0, 247 + (facelet_number % 9));
		break;
	}

	facelet_number++;
	facelet_number = facelet_number % 54;

	glVertex3f(xTL, yTL, zTL);
	glVertex3f(xBR, yBR, zBR);
	glVertex3f(xBL,  yBL,  zBL);

	glVertex3f(xTL, yTL, zTL);
	glVertex3f(xBR, yBR, zBR);
	glVertex3f(xTL + xBR - xBL, yTL + yBR - yBL, zTL + zBR - zBL);
	glEnd();
}

void draw9Squares3D(float xTL, float yTL, float zTL,
					float xBR, float yBR, float zBR,			//BR is the bottom right of the whole face
					float xBL, float yBL, float zBL) {
	
	//There are 2 perpendicular sides on a square
	//Any coordinate on the square can be defined as a ratio of each of the 2 vectors

	float TL_to_BL_x = xBL - xTL;
	float TL_to_BL_y = yBL - yTL;
	float TL_to_BL_z = zBL - zTL;

	float BL_to_BR_x = xBR - xBL;
	float BL_to_BR_y = yBR - yBL;
	float BL_to_BR_z = zBR - zBL;

	glColor3f(1.0, 1.0, 1.0);
	for (float i = 0; i != 60; i = i + 20) { //This for loop should be for the TL_to_BL vector

		float xTL_row = xTL + ((1 + i) / 60) * TL_to_BL_x;
		float yTL_row = yTL + ((1 + i) / 60) * TL_to_BL_y;
		float zTL_row = zTL + ((1 + i) / 60) * TL_to_BL_z;

		float xBL_row = xBL - ((41 - i) / 60) * TL_to_BL_x;
		float yBL_row = yBL - ((41 - i) / 60) * TL_to_BL_y;
		float zBL_row = zBL - ((41 - i) / 60) * TL_to_BL_z;
								 
		float xBR_row = xBR - ((41 - i) / 60) * TL_to_BL_x;
		float yBR_row = yBR - ((41 - i) / 60) * TL_to_BL_y;
		float zBR_row = zBR - ((41 - i) / 60) * TL_to_BL_z;

		for (float j = 0; j != 60; j = j + 20) {
			drawSquare3D(
						xTL_row + ((j + 1) / 60) * BL_to_BR_x, yTL_row + ((j + 1) / 60) * BL_to_BR_y, zTL_row + ((j + 1) / 60) * BL_to_BR_z,
						xBR_row - ((41 - j) / 60) * BL_to_BR_x, yBR_row - ((41 - j) / 60) * BL_to_BR_y, zBR_row - ((41 - j) / 60) * BL_to_BR_z,
						xBL_row + ((j + 1) / 60) * BL_to_BR_x, yBL_row + ((j + 1) / 60) * BL_to_BR_y, zBL_row + ((j + 1) / 60) * BL_to_BR_z			
			);
		}
	}


	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);


	for (float i = 0; i != 4; i++) {
		for (unsigned char i = 0; i != 80; i = i + 20) {
			//Vertical lines
			glVertex3f(xTL + (i * BL_to_BR_x / 60), yTL + (i * BL_to_BR_y / 60), zTL + (i * BL_to_BR_z / 60));
			glVertex3f(xBL + (i * BL_to_BR_x / 60), yBL + (i * BL_to_BR_y / 60), zBL + (i * BL_to_BR_z / 60));
			glVertex3f(xBL + (i + 1) * BL_to_BR_x / 60, yBL + (i + 1) * BL_to_BR_y / 60, zBL + (i + 1) * BL_to_BR_z / 60);

			glVertex3f(xTL + (i * BL_to_BR_x / 60), yTL + (i * BL_to_BR_y / 60), zTL + (i * BL_to_BR_z / 60));
			glVertex3f(xTL + (i + 1) * BL_to_BR_x / 60, yTL + (i + 1) * BL_to_BR_y / 60, zTL + (i + 1) * BL_to_BR_z / 60);
			glVertex3f(xBL + (i + 1) * BL_to_BR_x / 60, yBL + (i + 1) * BL_to_BR_y / 60, zBL + (i + 1) * BL_to_BR_z / 60);


			//Horizontal lines
			float xTR = xTL + xBR - xBL;
			float yTR = yTL + yBR - yBL;
			float zTR = zTL + zBR - zBL;

			glVertex3f(xTL + (i * TL_to_BL_x / 60), yTL + (i * TL_to_BL_y / 60), zTL + (i * TL_to_BL_z / 60));
			glVertex3f(xTL + (i + 1) * TL_to_BL_x / 60, yTL + (i + 1) * TL_to_BL_y / 60, zTL + (i + 1) * TL_to_BL_z / 60);
			glVertex3f(xTR + (i * TL_to_BL_x / 60), yTR + (i * TL_to_BL_y / 60), zTR + (i * TL_to_BL_z / 60));

			glVertex3f(xTR + ((i + 1) * TL_to_BL_x / 60), yTR + ((i + 1) * TL_to_BL_y / 60), zTR + ((i + 1) * TL_to_BL_z / 60));
			glVertex3f(xTL + (i + 1) * TL_to_BL_x / 60, yTL + (i + 1) * TL_to_BL_y / 60, zTL + (i + 1) * TL_to_BL_z / 60);
			glVertex3f(xTR + (i * TL_to_BL_x / 60), yTR + (i * TL_to_BL_y / 60), zTR + (i * TL_to_BL_z / 60));
		}
	}
	glEnd();
}


void draw3DCube(float xUFL, float yUFL, float zUFL,
				float xURF, float yURF, float zURF,	
				float xDLF, float yDLF, float zDLF,
				float xULB, float yULB, float zULB){

	//Each of the 8 corners of a cube will be referred to with cubie notation

	float xDown = xDLF - xUFL; float yDown = yDLF - yUFL; float zDown = zDLF - zUFL;
		
	float xUBR = xURF + xULB - xUFL; float yUBR = yURF + yULB - yUFL; float zUBR = zURF + zULB - zUFL;

	float xDFR = xURF + xDown; float yDFR = yURF + yDown; float zDFR = zURF + zDown;
	float xDLB = xULB + xDown; float yDLB = yULB + yDown; float zDLB = zULB + zDown;
	float xDBR = xUBR + xDown; float yDBR = yUBR + yDown; float zDBR = zUBR + zDown;


	//U face
	draw9Squares3D(	xULB, yULB, zULB,
					xURF, yURF, zURF,
					xUFL, yUFL, zUFL);

	//R face
	draw9Squares3D(	xURF, yURF, zURF,
					xDBR, yDBR, zDBR,
					xDFR, yDFR, zDFR);

	//F face
	draw9Squares3D(	xUFL, yUFL, zUFL,
					xDFR, yDFR, yDFR,
					xDLF, yDLF, zDLF);

	//D face
	draw9Squares3D(	xDLF, yDLF, zDLF,
					xDBR, yDBR, zDBR,
					xDLB, yDLB, zDLB);

	//L face
	draw9Squares3D(	xULB, yULB, zULB,
					xDLF, yDLF, zDLF,
					xDLB, yDLB, zDLB);

	//B face
	draw9Squares3D(	xDLB, yDLB, zDLB,
					xUBR, yUBR, zUBR,
					xULB, yULB, zULB);
}

void set_facelet_numbers(std::array <short, 54> perm) {
	for (unsigned short i = 0; i != 54; i++) {
		facelet_numbers[i] = perm[i];
	}
}


////U is white
////R is red
////F is green
////D is yellow
////L is orange
////B is blue