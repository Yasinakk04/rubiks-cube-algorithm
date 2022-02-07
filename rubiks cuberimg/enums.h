#pragma once
#include <array>

enum corners : short {
	URF,
	UFL,
	ULB,
	UBR,

	DFR,
	DLF,
	DBL,
	DRB
};

enum edges : short {
	UR,
	UF,
	UL,
	UB,

	DR,
	DF,
	DL,
	DB,

	FR,
	FL,
	BL,
	BR
};


enum facelets : short {
	U1, U2, U3, U4, U5, U6, U7, U8, U9,

	R1, R2, R3, R4, R5, R6, R7, R8, R9,

	F1, F2, F3, F4, F5, F6, F7, F8, F9,

	D1, D2, D3, D4, D5, D6, D7, D8, D9,

	L1, L2, L3, L4, L5, L6, L7, L8, L9,

	B1, B2, B3, B4, B5, B6, B7, B8, B9
};

/*		  U1 U2 U3
		  U4 U5 U6
		  U7 U8 U9

L1 L2 L3  F1 F2 F3  R1 R2 R3
L4 L5 L6  F4 F5 F6  R4 R5 R6
L7 L8 L9  F7 F8 F9  R7 R8 R9

		  D1 D2 D3
		  D4 D5 D6
		  D7 D8 D9

		  B1 B2 B3
		  B4 B5 B6
		  B7 B8 B9
_________________________________

		  0  1  2
		  3  4  5
		  6  7  8

36 37 38  18 19 20  9  10 11
39 40 41  21 22 23  12 13 14
42 43 44  24 25 26  15 16 17

		  27 28 29
		  30 31 32
		  33 34 35

		  45 46 47
		  48 49 50
		  51 52 53

*/

enum move : short {
	U, R, F, D, L, B
};

//const std::array <std::array <short, 3>, 8>  cornerFacelet = {
//	{facelets.F3, facelets.U9, facelets.R1},
//	{facelets.R3, facelets.U3, facelets.B9},
//	{facelets.L1, facelets.U1, facelets.B7},
//	{facelets.F1, facelets.U7, facelets.L3},
//	{facelets.F9, facelets.R7, facelets.D3},
//	{facelets.R9, facelets.D9, facelets.B3},
//	{facelets.L7, facelets.D7, facelets.B1},
//	{facelets.D7, facelets.B1, facelets.L9}
//};

//std::array <std::array <int, 3>, 12>  edgeFacelet =



const short No_corner = 8;
const short No_edge = 12;