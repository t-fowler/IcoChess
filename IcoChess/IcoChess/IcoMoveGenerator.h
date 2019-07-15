#pragma once
#ifndef ICO_MOVE_GENERATOR_H
#define ICO_MOVE_GENERATOR_H

class IcoMoveGenerator
{
private:
	int moveCount;
	Move* pawnMoves;
	Move* knightMoves;
	Move* bishopMoves;
	Move* rookMoves;
	Move* queenMoves;
	Move* kingMoves;

public:
	IcoMoveGenerator(Position* pos);
	~IcoMoveGenerator();
	bb64 pawnAttacksWest(bb64 pawns);
	bb64 pawnAttacksEast(bb64 pawns);
	bb64 pawnPushes(bb64 pawns);
	bb64 dblPawnPushes(bb64 pawns);
};

#endif		// Inclusion Guard