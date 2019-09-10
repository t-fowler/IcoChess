#pragma once
#ifndef ICO_MOVE_GENERATOR_H
#define ICO_MOVE_GENERATOR_H

class IcoMoveGenerator
{
private:
	int moveCount;
	CandidateMoveList quietMoves;

public:
	IcoMoveGenerator(Position &pos);
	~IcoMoveGenerator();
	bb64 pawnAttacksWest(bb64 pawns);
	bb64 pawnAttacksEast(bb64 pawns);
	bb64 dblPawnPushes(bb64 pawns);
	CandidateMoveList getMoveList();
};

#endif		// Inclusion Guard