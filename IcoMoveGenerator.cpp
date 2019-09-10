#include "IcoUtil.h"
#include "Move.h"
#include "BitManipulation.h"
#include "Position.h"

#include "IcoMoveGenerator.h"



IcoMoveGenerator::IcoMoveGenerator(Position &pos) {
	moveCount = 0;
	colour stm = pos.getStm();
	bb64 pawnPushTargets = 0,		pawnAttackTargets = 0,		kingMoveTargets = 0,
		 knightMoveTargets = 0,		BishopMoveTargets = 0,
		 rookMoveTargets = 0,		queenMoveTargets = 0;
	
	if (stm == WHITE) {
		/***********************************************************
		*				TODO: IMPLEMENT CASTLING				   *
		***********************************************************/

		/***********************************************************
		*						Pawn Pushes						   *
		***********************************************************/
		bb64 pawnsToMove = pos.getPieceBB(wPawns + stm);
		pawnPushTargets = (northOne(pawnsToMove) & pos.getEmptyBB()) | (northOne(northOne(pawnsToMove & RANKS[rank2]) & pos.getEmptyBB()) & pos.getEmptyBB());

		while (pawnPushTargets) {
			int toSquare = bitScanForward(pawnPushTargets);
			bb64 targetPawn = 1ULL << toSquare;
			int fromSquare;
			(southOne(targetPawn) & pawnsToMove) ? fromSquare = toSquare - 8 : fromSquare = toSquare - 16;
			unsigned int flag = 0;

			if ((1ULL << toSquare) & RANKS[rank8]) {
				flag = knPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
				flag = bPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
				flag = rPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
				flag = qPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
			}
			else if (southOne(southOne(targetPawn) & pawnsToMove))
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
			else
				quietMoves.add(Move(pos, fromSquare, toSquare, dblPawnPush));


			pawnPushTargets -= targetPawn;
		}
	} else {
		/***********************************************************
		*				TODO: IMPLEMENT CASTLING				   *
		***********************************************************/

		/***********************************************************
		*						Pawn Pushes						   *
		***********************************************************/
		bb64 pawnsToMove = pos.getPieceBB(wPawns + stm);
		pawnPushTargets = pawnPushTargets = (southOne(pawnsToMove) & pos.getEmptyBB()) | (southOne(southOne(pawnsToMove & RANKS[rank7]) & pos.getEmptyBB()) & pos.getEmptyBB());
		while (pawnPushTargets) {
			int toSquare = bitScanForward(pawnPushTargets);
			bb64 targetPawn = 1ULL << toSquare;
			int fromSquare;
			(northOne(targetPawn) & pawnsToMove) ? fromSquare = toSquare + 8 : fromSquare = toSquare + 16;
			unsigned int flag = 0;

			if ((1ULL << toSquare) & RANKS[rank1]) {
				flag = knPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
				flag = bPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
				flag = rPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
				flag = qPromo;
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
			}
			else if (northOne(northOne(targetPawn) & pawnsToMove))
				quietMoves.add(Move(pos, fromSquare, toSquare, flag));
			else
				quietMoves.add(Move(pos, fromSquare, toSquare, dblPawnPush));

			pawnPushTargets -= targetPawn;
		}
	}
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

bb64 IcoMoveGenerator::dblPawnPushes(bb64 pawns) {
	return 0ULL;
	/* Must check side to move for all of these */
}

CandidateMoveList IcoMoveGenerator::getMoveList() {
	return quietMoves;
}

