#pragma once

#include <array>
#include "enums.h"
#include "cubie.h"

inline cubie make_U_turn() {
	cubie U_turn;
	U_turn.set_corn_perm( { UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB });
	U_turn.set_corn_ori( { 0, 0, 0, 0, 0, 0, 0, 0 });
	U_turn.set_edge_perm( { UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR });
	U_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return U_turn;
}

inline cubie make_R_turn() {
	cubie R_turn;
	R_turn.set_corn_perm( { DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR });
	R_turn.set_corn_ori( { 2, 0, 0, 1, 1, 0, 0, 2 });
	R_turn.set_edge_perm( { FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR });
	R_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return R_turn;
}

inline cubie make_F_turn() {
	cubie F_turn;
	F_turn.set_corn_perm( { UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB });
	F_turn.set_corn_ori( { 1, 2, 0, 0, 2, 1, 0, 0 });
	F_turn.set_edge_perm( { UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR });
	F_turn.set_edge_ori( { 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0	});
	return F_turn;
}

inline cubie make_D_turn() {
	cubie D_turn;
	D_turn.set_corn_perm( { URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR });
	D_turn.set_corn_ori( { 0, 0, 0, 0, 0, 0, 0, 0 });
	D_turn.set_edge_perm( { UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR });
	D_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return D_turn;
}

inline cubie make_L_turn() {
	cubie L_turn;
	L_turn.set_corn_perm( { URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB });
	L_turn.set_corn_ori( { 0, 1, 2, 0, 0, 2, 1, 0 });
	L_turn.set_edge_perm( { UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR });
	L_turn.set_edge_ori( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	return L_turn;
}

inline cubie make_B_turn() {
	cubie B_turn;
	B_turn.set_corn_perm( { URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL });
	B_turn.set_corn_ori( { 0, 0, 1, 2, 0, 0, 2, 1 });
	B_turn.set_edge_perm( { UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB });
	B_turn.set_edge_ori( { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 });
	return B_turn;
}