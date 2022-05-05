#pragma once
#include "Position.h"
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Move.h"

namespace IcoChess
{

class IcoChessEngine
{
private:
	Position pos;
	CandidateMoveList quietMoves;

	void generatePawnMoves();

	void generateKnightMoves();

	void generateRookMoves();

	void generateBishopMoves();

	void generateQueenMoves();

	void generateKingMoves();

public:
	// Constructors
	IcoChessEngine();
	IcoChessEngine(Position p);

	// Move Generation
	void generateMoves();

	// Setters and Getters
	CandidateMoveList getMoves();
	Position getPosition();

	bb64 lineAttacks(int square);

	bb64 diagonalAttacks(int square);
};
}

