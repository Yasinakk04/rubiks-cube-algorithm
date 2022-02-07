#pragma once

#include "enums.h"
#include <string>
#include <array>


extern const std::string corn_pos[8];
extern const std::string edge_pos[12];

const std::array <std::array <short, 3>, 8>  cornerFacelet = { {
	{U9, R1, F3},
	{U7, F1, L3},
	{U1, L1, B7},
	{U3, B9, R3},

	{D3, F9, R7},
	{D1, L9, F7},
	{D7, B1, L7},
	{D9, R9, B3},
} };

const std::array <std::array <short, 3>, 8>  cornerColour = { {
	{U, R, F},
	{U, F, L},
	{U, L, B},
	{U, B, R},

	{D, F, R},
	{D, L, F},
	{D, B, L},
	{D, R, B},
} };

const std::array <std::array <short, 2>, 12>  edgeFacelet = { {
	{U6, R2},
	{U8, F2},
	{U4, L2},
	{U2, B8},

	{D6, R8},
	{D2, F8},
	{D4, L8},
	{D8, B2},

	{F6, R4},
	{F4, L6},
	{B4, L4},
	{B6, R6}
} };

const std::array <std::array <short, 2>, 12>  edgeColour = { {
	{U, R},
	{U, F},
	{U, L},
	{U, B},

	{D, R},
	{D, F},
	{D, L},
	{D, B},

	{F, R},
	{F, L},
	{B, L},
	{B, R}
} };