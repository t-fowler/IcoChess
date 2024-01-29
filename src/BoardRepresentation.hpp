#ifndef BOARD_REPRESENTATION_H
#define BOARD_REPRESENTATION_H

namespace IcoChess {

typedef unsigned long long bb64;
class Position;

enum Square
{	// Little endian rank-file ordering: sq = 8 * rankIndex + fileIndex.
    a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

enum Side : bool { WHITE, BLACK };

/********************************************************************
 *	pieceType	-- an enumeration used for accessing the correct
 *	index of the piecesBB array.
 ********************************************************************/
enum PieceType
{
	W_PAWN,		// White pawns
	W_KNIGHT,	// White knights
	W_BISHOP,	// White bishops
	W_ROOK,		// White rooks
	W_QUEEN,	// White queens
	W_KING,		// White king
	W_PIECE,	// White pieces
	B_PAWN,		// Black pawns
	B_KNIGHT,	// Black knights
	B_BISHOP,	// Black bishops
	B_ROOK,		// Black rooks
	B_QUEEN,	// Black queens
	B_KING,		// Black king
	B_PIECE,	// Black pieces
	NO_PIECE,	// No piece
	NUM_PIECE_TYPES // Number of piece types
};

enum CastleFlag {KINGSIDE = 1, QUEENSIDE};

const bb64
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
RANK_8 = 0xFF00000000000000;

} // IcoChess namespace

#endif