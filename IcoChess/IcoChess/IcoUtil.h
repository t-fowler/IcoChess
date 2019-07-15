#pragma once
#ifndef ICOUTIL_H
#define ICOUTIL_H
typedef unsigned long long bb64;
class Position; 

enum flags {			// Move flags
	quietMove,				// 0000 
	dblPawnPush,			// 0001
	kingCastle,				// 0010
	queenCastle,			// 0011
	capture,				// 0100
	enPassant,				// 0101
	knPromo,				// 1000
	bPromo,					// 1001
	rPromo,					// 1010
	qPromo,					// 1011
	knPromoCapture,			// 1100
	bPromoCapture,			// 1101
	rPromoCapture,			// 1110
	qpromoCapture			// 1111
};

enum colour : bool { WHITE, BLACK };
colour other(colour side);	// returns the colour opposite to side

enum squares {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

enum pieceType {
	wPawns,		// White pawns
	bPawns,		// Black pawns
	wKnights,	// White knights
	bKnights,	// Black knights
	wBishops,	// White bishops
	bBishops,	// Black bishops
	wRooks,		// White rooks
	bRooks,		// Black rooks
	wQueens,	// White queens
	bQueens,	// Black queens
	wKing,		// White king
	bKing,		// Black king
	wPieces,	// White pieces
	bPieces,	// Black pieces
	noPiece		// No piece
};

enum direction {
	NORTH,
	N_EAST,
	EAST,
	S_EAST,
	SOUTH,
	S_WEST,
	WEST,
	N_WEST
};

enum file {
	aFile,
	bFile,
	cFile,
	dFile,
	eFile,
	fFile,
	gFile,
	hFile
};

enum rank {
	rank1,
	rank2,
	rank3,
	rank4,
	rank5,
	rank6,
	rank7,
	rank8
};

const bb64 FILES[8] = 
{0x0101010101010101, 0x0202020202020202,
 0x0404040404040404, 0x0808080808080808,
 0x1010101010101010, 0x2020202020202020,
 0x4040404040404040, 0x8080808080808080};
const bb64 RANKS[8] = 
{0x00000000000000FF, 0x000000000000FF00,
 0x0000000000FF0000, 0x00000000FF000000,
 0x000000FF00000000, 0x0000FF0000000000,
 0x00FF000000000000, 0xFF00000000000000};

extern const bb64 ATTACK_RAYS[64][8];

/****************************************************************
*		printChessBoard prints a position to the console		*
*	such that it is readable as a chessboard.					*
*																*
*	@Position pos -- the position to be printed.				*
****************************************************************/
void printChessBoard(Position pos);

#endif			// Inclusion guard