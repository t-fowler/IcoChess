#include <iostream>

#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"

namespace IcoChess
{

std::array<std::array<bb64, 8>, 64> initAttackRays()
{
	std::array<std::array<bb64, 8>, 64> result;

	// Generate sliding attacks to the north.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][NORTH] = 0;
		for (bb64 tmp = northOne(1ULL << sq); tmp != 0; tmp = northOne(tmp)) {
			result[sq][NORTH] |= tmp;
		}
	}
	// Generate sliding attacks to the east.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][EAST] = 0;
		for (bb64 tmp = eastOne(1ULL << sq); tmp != 0; tmp = eastOne(tmp)) {
			result[sq][EAST] |= tmp;
		}
	}
	// Generate sliding attacks to the south.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][SOUTH] = 0;
		for (bb64 tmp = southOne(1ULL << sq); tmp != 0; tmp = southOne(tmp)) {
			result[sq][SOUTH] |= tmp;
		}
	}
	// Generate sliding attacks to the west.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][WEST] = 0;
		for (bb64 tmp = westOne(1ULL << sq); tmp != 0; tmp = westOne(tmp)) {
			result[sq][WEST] |= tmp;
		}
	}
	// Generate sliding attacks to the northWest.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][NORTH_WEST] = 0;
		for (bb64 tmp = norWestOne(1ULL << sq); tmp != 0; tmp = norWestOne(tmp)) {
			result[sq][NORTH_WEST] |= tmp;
		}
	}
	// Generate sliding attacks to the northEast.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][NORTH_EAST] = 0;
		for (bb64 tmp = norEastOne(1ULL << sq); tmp != 0; tmp = norEastOne(tmp)) {
			result[sq][NORTH_EAST] |= tmp;
		}
	}
	// Generate sliding attacks to the southWest.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][SOUTH_WEST] = 0;
		for (bb64 tmp = souWestOne(1ULL << sq); tmp != 0; tmp = souWestOne(tmp)) {
			result[sq][SOUTH_WEST] |= tmp;
		}
	}
	// Generate sliding attacks to the southEast.
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][SOUTH_EAST] = 0;
		for (bb64 tmp = souEastOne(1ULL << sq); tmp != 0; tmp = souEastOne(tmp)) {
			result[sq][SOUTH_EAST] |= tmp;
		}
	}
	/*
	// Generate bishop attacks
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][0] = northEastAttacks[sq] | northWestAttacks[sq]
			| southEastAttacks[sq] | southWestAttacks[sq];
	}

	// Generate rook attacks
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][1] = northAttacks[sq] | southAttacks[sq]
			| westAttacks[sq] | eastAttacks[sq];
	}

	// Generate Queen attacks
	for (int sq = a1; sq <= h8; sq++) {
		result[sq][2] = result[sq][0] | result[sq][1];
	}
	*/
	return result;
}

std::array<bb64, 64> initKnightAttacks()
{
	std::array<bb64, 64> result;
	for (int sq = a1; sq <= h8; sq++) {
		bb64 knight = 1ULL << sq;
		result[sq] = 0;
		result[sq] = northOne(norEastOne(knight))
				   | eastOne(norEastOne(knight))
				   | eastOne(souEastOne(knight))
				   | southOne(souEastOne(knight))
				   | southOne(souWestOne(knight))
				   | westOne(souWestOne(knight))
				   | westOne(norWestOne(knight))
				   | northOne(norWestOne(knight));
	}
	return result;
}

std::array<bb64, 64> initKingAttacks()
{
	std::array<bb64, 64> result;
	for (int sq = a1; sq <= h8; sq++) {
		bb64 king = 1ULL << sq;
		result[sq] = northOne(king)
				   | norEastOne(king)
				   | eastOne(king)
				   | souEastOne(king)
			       | southOne(king)
			       | souWestOne(king)
				   | westOne(king)
				   | norWestOne(king);
	}
	return result;
}

/****************************************************************
*		printChessBoard prints one rank at a time starting		*
*	on the black side (rank 7), checking if each square is		*
*	occupied before checking which piece occupies the square	*
*	and printing to the console.								*
*		Capital letters represent white pieces and lower case	*
*	characters represent the black pieces.						*
****************************************************************/
void printChessBoard(Position pos)
{
	std::cout << "---------------------------------" << std::endl;
	for (int rank = 7; rank >= 0; rank--) {
		for (int file = 0; file < 8; file++) {
			int index = (8 * rank + file);
			if (bbBitTest(pos.getOccupiedBB(), index)) {
				int pt;
				for (pt = W_PAWN; pt <= B_KING; pt++) {
					if (bbBitTest(pos.getPieceBB(pieceType(pt)), index)) {
						switch (pieceType(pt)) {
						case W_PAWN:
							std::cout << "| P ";
							break;
						case B_PAWN:
							std::cout << "| p ";
							break;
						case W_KNIGHT:
							std::cout << "| N ";
							break;
						case B_KNIGHT:
							std::cout << "| n ";
							break;
						case W_BISHOP:
							std::cout << "| B ";
							break;
						case B_BISHOP:
							std::cout << "| b ";
							break;
						case W_ROOK:
							std::cout << "| R ";
							break;
						case B_ROOK:
							std::cout << "| r ";
							break;
						case W_QUEEN:
							std::cout << "| Q ";
							break;
						case B_QUEEN:
							std::cout << "| q ";
							break;
						case W_KING:
							std::cout << "| K ";
							break;
						case B_KING:
							std::cout << "| k ";
							break;
						default:
							break;
						}
						break;
					}
				}
			}
			else {
				std::cout << "|   ";
			}
		}
		std::cout << "|";
		std::cout << std::endl << "---------------------------------" << std::endl;
	}
	std::cout << std::endl;
}

/****************************************************************
*		printMove relies on the fact that the scalar index		*
*	for a chess square can be converted into the rank and file	*
*	indexes via the folowing formulas:							*
*																*
*				fileIndex = squareIndex modulo 8				*
*				rankIndex = squareIndex div    8				*
*																*
*		These indexes are then converted into a n algebraic		*
*	chess notation to be printed.								*
****************************************************************/
void printMove(Move mov)
{
	int fromSquare = mov.getFromSquare();
	int toSquare = mov.getToSquare();
	int fromFile = fromSquare % 8;
	int fromRank = fromSquare / 8;
	int toFile = toSquare % 8;
	int toRank = toSquare / 8;

	switch (mov.getMovPiece()) {
	case W_PAWN:
	case B_PAWN:
		if (mov.getFlags() & 0b0100) {
			switch (fromFile) {
			case 0:
				std::cout << 'a';
				break;
			case 1:
				std::cout << 'b';
				break;
			case 2:
				std::cout << 'c';
				break;
			case 3:
				std::cout << 'd';
				break;
			case 4:
				std::cout << 'e';
				break;
			case 5:
				std::cout << 'f';
				break;
			case 6:
				std::cout << 'g';
				break;
			case 7:
				std::cout << 'h';
				break;
			}
		}
		break;
	case W_BISHOP:
	case B_BISHOP:
		std::cout << 'B';
		break;
	case W_KNIGHT:
	case B_KNIGHT:
		std::cout << 'N';
		break;
	case W_ROOK:
	case B_ROOK:
		std::cout << 'R';
		break;
	case W_QUEEN:
	case B_QUEEN:
		std::cout << 'Q';
		break;
	case W_KING:
	case B_KING:
		std::cout << 'K';
		break;
	}

	if (mov.getFlags() & 0b0100) {
		std::cout << 'x';
	}

	switch (toFile) {
	case 0:
		std::cout << 'a';
		break;
	case 1:
		std::cout << 'b';
		break;
	case 2:
		std::cout << 'c';
		break;
	case 3:
		std::cout << 'd';
		break;
	case 4:
		std::cout << 'e';
		break;
	case 5:
		std::cout << 'f';
		break;
	case 6:
		std::cout << 'g';
		break;
	case 7:
		std::cout << 'h';
		break;
	}

	switch (toRank) {
	case 0:
		std::cout << '1';
		break;
	case 1:
		std::cout << '2';
		break;
	case 2:
		std::cout << '3';
		break;
	case 3:
		std::cout << '4';
		break;
	case 4:
		std::cout << '5';
		break;
	case 5:
		std::cout << '6';
		break;
	case 6:
		std::cout << '7';
		break;
	case 7:
		std::cout << '8';
		break;
	}
}
}
