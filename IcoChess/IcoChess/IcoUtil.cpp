#include <iostream>
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"

void utilInit()
{
	bb64 rayAttacks[64][8];
	/****************************************************************
	*		Initialize ATTACK_RAYS in positive directions			*
	****************************************************************/
	bb64 ray = 0x0101010101010100;		// NORTH DIRECTION
	for (int sq = 0; sq < 64; sq++, ray <<= 1) {
		rayAttacks[sq][NORTH] = ray;
	}

	ray = 0x8040201008040200;
	for (int file = 0; file < 8; file++, ray = eastOne(ray)) {

	}
}

colour other(colour side)
{
	return colour(!side);
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
				for (pt = wPawns; pt <= bKing; pt++) {
					if (bbBitTest(pos.getPieceBB(pieceType(pt)), index)) {
						switch (pt) {
							case wPawns:
								std::cout << "| P ";
								break;
							case bPawns:
								std::cout << "| p ";
								break;
							case wKnights:
								std::cout << "| N ";
								break;
							case bKnights:
								std::cout << "| n ";
								break;
							case wBishops:
								std::cout << "| B ";
								break;
							case bBishops:
								std::cout << "| b ";
								break;
							case wRooks:
								std::cout << "| R ";
								break;
							case bRooks:
								std::cout << "| r ";
								break;
							case wQueens:
								std::cout << "| Q ";
								break;
							case bQueens:
								std::cout << "| q ";
								break;
							case wKing:
								std::cout << "| K ";
								break;
							case bKing:
								std::cout << "| k ";
								break;
							default:
								break;
						}
						break;
					}
				}
			}
			else std::cout << "|   ";
		}
		std::cout << "|";
		std::cout << std::endl << "---------------------------------" << std::endl;
	}
		std::cout << std::endl;
}
