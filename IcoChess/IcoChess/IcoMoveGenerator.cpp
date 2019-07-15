#include "IcoUtil.h"
#include "Move.h"
#include "BitManipulation.h"
#include "Position.h"

#include "IcoMoveGenerator.h"



IcoMoveGenerator::IcoMoveGenerator(Position* pos) {
	moveCount = 0;
	colour stm = pos->getStm();
	bb64 pawnPushTargets = 0, pawnAttackTargets = 0,
		knightMoveTargets = 0, bishopMoveTargets = 0,
		rookMoveTargets = 0, queenMoveTargets = 0, kingMoveTargets = 0;

	/***********************************************************
	*				TODO: IMPLEMENT CASTLING				   *
	***********************************************************/
	
	/***********************************************************
	*						Pawn Pushes						   *
	***********************************************************/
	//for (int i = 0; i < popCount64(pos->get))
}

IcoMoveGenerator::~IcoMoveGenerator() {
}

/* Must check side to move for all of these */
bb64 IcoMoveGenerator::pawnAttacksWest(bb64 pawns) {
	return (pawns << 7) & ~hFile;
}

bb64 IcoMoveGenerator::pawnAttacksEast(bb64 pawns) {
	return (pawns << 9) & ~aFile;
}

bb64 IcoMoveGenerator::pawnPushes(bb64 pawns) {
	return (pawns << 8);
}
bb64 IcoMoveGenerator::dblPawnPushes(bb64 pawns) {
	return 0ULL;
	/* Must check side to move for all of these */
}
