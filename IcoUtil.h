#pragma once
#ifndef ICOUTIL_H
#define ICOUTIL_H
#include <array>

namespace IcoChess {

typedef unsigned long long bb64;
class Position;
class Move;

enum square
{
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

enum flag
{	// Move flags
	QUIET_MOVE = 0b0000,
	DOUBLE_PAWN_PUSH = 0b0001,
	KINGSIDE_CASTLE = 0b0010,
	QUEENSIDE_CASTLE = 0b0011,
	CAPTURE = 0b0100,
	EN_PASSANT = 0b0101,
	PROMOTE_TO_KNIGHT = 0b1000,
	PROMOTE_TO_BISHOP = 0b1001,
	PROMOTE_TO_ROOK = 0b1010,
	PROMOTE_TO_QUEEN = 0b1011,
	PROMOTE_TO_KNIGHTCAPTURE = 0b1100,
	PROMOTE_TO_BISHOPCAPTURE = 0b1101,
	PROMOTE_TO_ROOKCAPTURE = 0b1110,
	PROMOTE_TO_QUEENCAPTURE = 0b1111
};

enum colour : bool { WHITE, BLACK };
colour other(colour side);	// returns the colour opposite to side

/********************************************************************
 *	pieceType	-- an enumeration used for accessing the correct	*
 *	index of the piecesBB array.									*
 ********************************************************************/
enum pieceType
{
	W_PAWN,		// White pawns
	B_PAWN,		// Black pawns
	W_KNIGHT,	// White knights
	B_KNIGHT,	// Black knights
	W_BISHOP,	// White bishops
	B_BISHOP,	// Black bishops
	W_ROOK,		// White rooks
	B_ROOK,		// Black rooks
	W_QUEEN,	// White queens
	B_QUEEN,	// Black queens
	W_KING,		// White king
	B_KING,		// Black king
	W_PIECE,	// White pieces
	B_PIECE,	// Black pieces
	NO_PIECE	// No piece
};

enum direction
{
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST
};

constexpr bb64
A_FILE = 0x0101010101010101,
B_FILE = 0x0202020202020202,
C_FILE = 0x0404040404040404,
D_FILE = 0x0808080808080808,
E_FILE = 0x1010101010101010,
F_FILE = 0x2020202020202020,
G_FILE = 0x4040404040404040,
H_FILE = 0x8080808080808080,

RANK_1 = 0x00000000000000FF,
RANK_2 = 0x000000000000FF00,
RANK_3 = 0x0000000000FF0000,
RANK_4 = 0x00000000FF000000,
RANK_5 = 0x000000FF00000000,
RANK_6 = 0x0000FF0000000000,
RANK_7 = 0x00FF000000000000,
RANK_8 = 0xFF00000000000000,

A1_H8_DIAGONAL = 0x8040201008040201,
A2_G8_DIAGONAL = 0x4020100804020100,
A3_F8_DIAGONAL = 0x2010080402010000,
A4_E8_DIAGONAL = 0x1008040201000000,
A5_D8_DIAGONAL = 0x0804020100000000,
A6_C8_DIAGONAL = 0x0402010000000000,
A7_B8_DIAGONAL = 0x0201000000000000,
A8_A8_DIAGONAL = 0x0100000000000000,
H1_H1_DIAGONAL = 0x0000000000000080,
G1_H2_DIAGONAL = 0x0000000000008040,
F1_H3_DIAGONAL = 0x0000000000804020,
E1_H4_DIAGONAL = 0x0000000080402010,
D1_H5_DIAGONAL = 0x0000008040201008,
C1_H6_DIAGONAL = 0x0000804020100804,
B1_H7_DIAGONAL = 0x0080402010080402,

A8_H1_DIAGONAL = 0x0102040810204080,
A7_G1_DIAGONAL = 0x0001020408102040,
A6_F1_DIAGONAL = 0x0000010204081020,
A5_E1_DIAGONAL = 0x0000000102040810,
A4_D1_DIAGONAL = 0x0000000001020408,
A3_C1_DIAGONAL = 0x0000000000010204,
A2_B1_DIAGONAL = 0x0000000000000102,
A1_A1_DIAGONAL = 0x0000000000000001,
H8_H8_DIAGONAL = 0x8000000000000000,
G8_H7_DIAGONAL = 0x4080000000000000,
F8_H6_DIAGONAL = 0x2040800000000000,
E8_H5_DIAGONAL = 0x1020408000000000,
D8_H4_DIAGONAL = 0x0810204080000000,
C8_H3_DIAGONAL = 0x0408102040800000,
B8_H2_DIAGONAL = 0x0204081020408000;

constexpr bb64 FILE[8] = { A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE };

constexpr bb64 RANK[8] = { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };

constexpr bb64 DIAGONAL[16] = { 
	A1_H8_DIAGONAL, A2_G8_DIAGONAL, A3_F8_DIAGONAL, A4_E8_DIAGONAL,
	A5_D8_DIAGONAL, A6_C8_DIAGONAL, A7_B8_DIAGONAL, A8_A8_DIAGONAL,
	0,				H1_H1_DIAGONAL, G1_H2_DIAGONAL, F1_H3_DIAGONAL,
	E1_H4_DIAGONAL, D1_H5_DIAGONAL, C1_H6_DIAGONAL, B1_H7_DIAGONAL
};

constexpr bb64 ANTI_DIAGONAL[16] = {
	A8_H1_DIAGONAL, A7_G1_DIAGONAL, A6_F1_DIAGONAL, A5_E1_DIAGONAL,
	A4_D1_DIAGONAL, A3_C1_DIAGONAL, A2_B1_DIAGONAL, A1_A1_DIAGONAL,
	0,				H8_H8_DIAGONAL, G8_H7_DIAGONAL, F8_H6_DIAGONAL,
	E8_H5_DIAGONAL, D8_H4_DIAGONAL, C8_H3_DIAGONAL, B8_H2_DIAGONAL
};

std::array<std::array<bb64, 8>, 64> initAttackRays();

const std::array<std::array<bb64, 8>, 64> ATTACK_RAYS = initAttackRays();

//const std::array<std::array<bb64, 64>, 6> PIECE_ATTACKS = initPieceAttacks();

/****************************************************************
*		printChessBoard prints a position to the console		*
*	such that it is readable as a chessboard.					*
*																*
*	@Position pos -- the position to be printed.				*
****************************************************************/
void printChessBoard(Position pos);

/****************************************************************
*		printMov prints the algebraic notation for the given	*
*	chess move.													*
*																*
*	@Move mov -- the chess move to be printed.					*
****************************************************************/
void printMove(Move mov);

}

#endif			// Inclusion guard