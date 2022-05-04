#include "IcoChessEngine.h"

namespace IcoChess
{

IcoChessEngine::IcoChessEngine()
{
	pos = Position();
	quietMoves = CandidateMoveList();
}

IcoChessEngine::IcoChessEngine(Position p)
{
	pos = p;
	quietMoves = CandidateMoveList();
}

void IcoChessEngine::generateMoves()
{
	/***********************************************************
	*				TODO: IMPLEMENT CASTLING				   *
	***********************************************************/

	generatePawnMoves();
	generateBishopMoves();
	generateRookMoves();
	generateQueenMoves();
}

void IcoChessEngine::generatePawnMoves()
{
	if (pos.getStm() == WHITE) {
		bb64 pawnsToMove = pos.getPieceBB(W_PAWN);
		bb64 singlePushTargets = northOne(pawnsToMove) & pos.getEmptyBB();
		bb64 dblPushTargets = (northOne(singlePushTargets) & RANK_4) & pos.getEmptyBB();
		bb64 pawnAttackTargets = (norEastOne(pawnsToMove) | norWestOne(pawnsToMove)) & pos.getPieceBB(B_PIECE);
		bb64 EN_PASSANTTargets = pos.getEN_PASSANTTarget();

		if (EN_PASSANTTargets) {
			int toSquare = bitScanForward(EN_PASSANTTargets) + 8;
			int fromSquare = toSquare - 9; // Valid EN_PASSANTTargets will not result in fromSquare == 0

			if (fromSquare & ~H_FILE && pos.getPieceOnSquare(fromSquare) == W_PAWN) {
				quietMoves.add(Move(pos, fromSquare, toSquare, EN_PASSANT));
			}
			fromSquare = toSquare - 7;
			if (fromSquare & ~A_FILE && pos.getPieceOnSquare(fromSquare) == W_PAWN) {
				quietMoves.add(Move(pos, fromSquare, toSquare, EN_PASSANT));
			}
		}

		while (singlePushTargets) {
			int toSquare = bitScanForward(singlePushTargets);
			int fromSquare = toSquare - 8;

			// Check for promotion and add moves to the move list.
			if ((1ULL << toSquare) & RANK_8) {
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_KNIGHT));
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_BISHOP));
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_ROOK));
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_QUEEN));
			}
			else {
				quietMoves.add(Move(pos, fromSquare, toSquare, 0));
			}

			// Remove processed target.
			bbResetBit(singlePushTargets, toSquare);
		}

		while (dblPushTargets) {
			int toSquare = bitScanForward(dblPushTargets);
			int fromSquare = toSquare - 16;
			unsigned int flag = DOUBLE_PAWN_PUSH;

			// No promotions needed since pawns can only double move to the fourth rank.
			quietMoves.add(Move(pos, fromSquare, toSquare, DOUBLE_PAWN_PUSH));
			bbResetBit(dblPushTargets, toSquare);
		}

		while (pawnAttackTargets) {
			int toSquare = bitScanForward(pawnAttackTargets);
			int fromSquare;
			bb64 targetCAPTURE = 1ULL << toSquare;

			// Add pawn moves attacking to the west.
			if (souEastOne(targetCAPTURE) & pawnsToMove) {
				fromSquare = toSquare - 7;
				if (targetCAPTURE & RANK_8) { // Check if promotions.
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_KNIGHTCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_BISHOPCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_ROOKCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_QUEENCAPTURE));
				}
				else {
					quietMoves.add(Move(pos, fromSquare, toSquare, CAPTURE));
				}
			}
			// Repeat for east attacks.
			if (souWestOne(targetCAPTURE) & pawnsToMove) {
				fromSquare = toSquare - 9;
				if (targetCAPTURE & RANK_8) { // Check if promotion.
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_KNIGHTCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_BISHOPCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_ROOKCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_QUEENCAPTURE));
				}
				else {
					quietMoves.add(Move(pos, fromSquare, toSquare, CAPTURE));
				}
			}

			// Remove processed target.
			bbResetBit(pawnAttackTargets, toSquare);
		}
	}
	else if (pos.getStm() == BLACK) {
		bb64 pawnsToMove = pos.getPieceBB(B_PAWN);
		bb64 singlePushTargets = southOne(pawnsToMove) & pos.getEmptyBB();
		bb64 dblPushTargets = (southOne(singlePushTargets) & RANK_5) & pos.getEmptyBB();
		bb64 pawnAttackTargets = (souEastOne(pawnsToMove) | souWestOne(pawnsToMove)) & pos.getPieceBB(W_PIECE);
		bb64 EN_PASSANTTargets = pos.getEN_PASSANTTarget();

		if (EN_PASSANTTargets) {
			unsigned int toSquare = bitScanForward(EN_PASSANTTargets) - 8;
			unsigned int fromSquare = toSquare + 7; // Valid EN_PASSANTTargets will not result in fromSquare == 0

			if (fromSquare & ~H_FILE && pos.getPieceOnSquare(fromSquare) == B_PAWN) {
				quietMoves.add(Move(pos, fromSquare, toSquare, EN_PASSANT));
			}
			fromSquare = toSquare + 9;
			if (fromSquare & ~A_FILE && pos.getPieceOnSquare(fromSquare) == B_PAWN) {
				quietMoves.add(Move(pos, fromSquare, toSquare, EN_PASSANT));
			}
		}

		while (singlePushTargets) {
			int toSquare = bitScanForward(singlePushTargets);
			int fromSquare = toSquare + 8;

			// Check for promotion and add moves to the move list.
			if ((1ULL << toSquare) & RANK_1) {
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_KNIGHT));
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_BISHOP));
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_ROOK));
				quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_QUEEN));
			}
			else {
				quietMoves.add(Move(pos, fromSquare, toSquare, 0));
			}

			// Remove processed target.
			bbResetBit(singlePushTargets, toSquare);
		}

		while (dblPushTargets) {
			int toSquare = bitScanForward(dblPushTargets);
			int fromSquare = toSquare + 16;
			unsigned int flag = DOUBLE_PAWN_PUSH;

			// No promotions needed since pawns can only double move to the fourth rank.
			quietMoves.add(Move(pos, fromSquare, toSquare, DOUBLE_PAWN_PUSH));
			bbResetBit(dblPushTargets, toSquare);
		}

		while (pawnAttackTargets) {
			int toSquare = bitScanForward(pawnAttackTargets);
			int fromSquare;
			bb64 targetCAPTURE = 1ULL << toSquare;

			// Add pawn moves attacking to the west.
			if (norEastOne(targetCAPTURE) & pawnsToMove) {
				fromSquare = toSquare + 9;
				if (targetCAPTURE & RANK_1) { // Check if promotions.
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_KNIGHTCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_BISHOPCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_ROOKCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_QUEENCAPTURE));
				}
				else {
					quietMoves.add(Move(pos, fromSquare, toSquare, CAPTURE));
				}
			}
			// Repeat for east attacks.
			if (norWestOne(targetCAPTURE) & pawnsToMove) {
				fromSquare = toSquare + 7;
				if (targetCAPTURE & RANK_1) { // Check if promotion.
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_KNIGHTCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_BISHOPCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_ROOKCAPTURE));
					quietMoves.add(Move(pos, fromSquare, toSquare, PROMOTE_TO_QUEENCAPTURE));
				}
				else {
					quietMoves.add(Move(pos, fromSquare, toSquare, CAPTURE));
				}
			}

			// Remove processed target.
			bbResetBit(pawnAttackTargets, toSquare);
		}
	}
}

void IcoChessEngine::generateKnightMoves() 
{

}

void IcoChessEngine::generateRookMoves()
{
	if (pos.getStm() == WHITE) {
		bb64 rooks = pos.getPieceBB(W_ROOK);
		while (rooks) {
			unsigned int fromSquare = bitScanForward(rooks);
			bb64 targets = lineAttacks(fromSquare);

			// remove processed rook
			bbResetBit(rooks, fromSquare);

			while (targets) {
				unsigned int flags = QUIET_MOVE;
				unsigned int toSquare = bitScanForward(targets);
				bb64 targetSquare = 1ULL << toSquare;

				// Remove processed target square.
				bbResetBit(targets, toSquare);

				// Check for collision with another piece.
				if (targetSquare & pos.getPieceBB(W_PIECE)) {
					continue;
				}
				else if (targetSquare & pos.getPieceBB(B_PIECE)) {
					flags |= CAPTURE;
				}

				// Add move to move list.
				quietMoves.add(Move(pos, fromSquare, toSquare, flags));
			}
		}
	}
	else if (pos.getStm() == BLACK) {
		bb64 rooks = pos.getPieceBB(B_ROOK);
		while (rooks) {
			unsigned int fromSquare = bitScanForward(rooks);
			bb64 targets = lineAttacks(fromSquare);

			// remove processed rook
			bbResetBit(rooks, fromSquare);

			while (targets) {
				unsigned int flags = QUIET_MOVE;
				unsigned int toSquare = bitScanForward(targets);
				bb64 targetSquare = 1ULL << toSquare;

				// Remove processed target square.
				bbResetBit(targets, toSquare);

				// Check for collision with another piece.
				if (targetSquare & pos.getPieceBB(B_PIECE)) {
					continue;
				}
				else if (targetSquare & pos.getPieceBB(W_PIECE)) {
					flags |= CAPTURE;
				}

				// Add move to move list.
				quietMoves.add(Move(pos, fromSquare, toSquare, flags));
			}
		}
	}
}


void IcoChessEngine::generateBishopMoves()
{
	if (pos.getStm() == WHITE) {
		bb64 bishops = pos.getPieceBB(W_BISHOP);
		while (bishops) {
			unsigned int fromSquare = bitScanForward(bishops);
			bb64 targets = diagonalAttacks(fromSquare);

			// remove processed rook
			bbResetBit(bishops, fromSquare);

			while (targets) {
				unsigned int flags = QUIET_MOVE;
				unsigned int toSquare = bitScanForward(targets);
				bb64 targetSquare = 1ULL << toSquare;

				// Remove processed target square.
				bbResetBit(targets, toSquare);

				// Check for collision with another piece.
				if (targetSquare & pos.getPieceBB(W_PIECE)) {
					continue;
				}
				else if (targetSquare & pos.getPieceBB(B_PIECE)) {
					flags |= CAPTURE;
				}

				// Add move to move list.
				quietMoves.add(Move(pos, fromSquare, toSquare, flags));
			}
		}
	}
	else if (pos.getStm() == BLACK) {
		bb64 bishops = pos.getPieceBB(B_BISHOP);
		while (bishops) {
			unsigned int fromSquare = bitScanForward(bishops);
			bb64 targets = diagonalAttacks(fromSquare);

			// remove processed rook
			bbResetBit(bishops, fromSquare);

			while (targets) {
				unsigned int flags = QUIET_MOVE;
				unsigned int toSquare = bitScanForward(targets);
				bb64 targetSquare = 1ULL << toSquare;

				// Remove processed target square.
				bbResetBit(targets, toSquare);

				// Check for collision with another piece.
				if (targetSquare & pos.getPieceBB(B_PIECE)) {
					continue;
				}
				else if (targetSquare & pos.getPieceBB(W_PIECE)) {
					flags |= CAPTURE;
				}

				// Add move to move list.
				quietMoves.add(Move(pos, fromSquare, toSquare, flags));
			}
		}
	}
}

void IcoChessEngine::generateQueenMoves()
{
	if (pos.getStm() == WHITE) {
		bb64 queens = pos.getPieceBB(W_QUEEN);
		while (queens) {
			unsigned int fromSquare = bitScanForward(queens);
			bb64 targets = lineAttacks(fromSquare) 
				         | diagonalAttacks(fromSquare);

			// remove processed rook
			bbResetBit(queens, fromSquare);

			while (targets) {
				unsigned int flags = QUIET_MOVE;
				unsigned int toSquare = bitScanForward(targets);
				bb64 targetSquare = 1ULL << toSquare;

				// Remove processed target square.
				bbResetBit(targets, toSquare);

				// Check for collision with another piece.
				if (targetSquare & pos.getPieceBB(W_PIECE)) {
					continue;
				}
				else if (targetSquare & pos.getPieceBB(B_PIECE)) {
					flags |= CAPTURE;
				}

				// Add move to move list.
				quietMoves.add(Move(pos, fromSquare, toSquare, flags));
			}
		}
	}
	else if (pos.getStm() == BLACK) {
		bb64 queens = pos.getPieceBB(B_QUEEN);
		while (queens) {
			unsigned int fromSquare = bitScanForward(queens);
			bb64 targets = lineAttacks(fromSquare)
						 | diagonalAttacks(fromSquare);

			// remove processed rook
			bbResetBit(queens, fromSquare);

			while (targets) {
				unsigned int flags = QUIET_MOVE;
				unsigned int toSquare = bitScanForward(targets);
				bb64 targetSquare = 1ULL << toSquare;

				// Remove processed target square.
				bbResetBit(targets, toSquare);

				// Check for collision with another piece.
				if (targetSquare & pos.getPieceBB(B_PIECE)) {
					continue;
				}
				else if (targetSquare & pos.getPieceBB(W_PIECE)) {
					flags |= CAPTURE;
				}

				// Add move to move list.
				quietMoves.add(Move(pos, fromSquare, toSquare, flags));
			}
		}
	}
}

bb64 IcoChessEngine::lineAttacks(int square)
{
	if (square < 0 || square > 63) 
		throw std::out_of_range("lineAttacks called on out of range square.");

	bb64 occupied = pos.getOccupiedBB(),
		 slider = 1ULL << square,
		 horizontalMask = RANK[square / 8],
		 verticalMask = FILE[square % 8];

	bb64 horizontalAttacks = (((occupied & horizontalMask) - 2 * slider)
						   ^ bbReverse(bbReverse(occupied & horizontalMask) 
									   - 2* bbReverse(slider))) 
						   & horizontalMask;

	bb64 verticalAttacks = (((occupied & verticalMask) - 2 * slider)
						 ^ bbReverse(bbReverse(occupied & verticalMask) 
									 - 2 * bbReverse(slider))) 
						 & verticalMask;

	return horizontalAttacks | verticalAttacks;
}

/*
 * 
 *
 *
 */
bb64 IcoChessEngine::diagonalAttacks(int square)
{
	if (square < 0 || square > 63) 
		throw std::out_of_range("lineAttacks called on out of range square.");

	bb64 occupied = pos.getOccupiedBB(), slider = 1ULL << square,
		diagonalMask = DIAGONAL[((square / 8) - (square % 8)) & 15],
		antiDiagonalMask = ANTI_DIAGONAL[((square / 8) + (square % 8)) ^ 7];

	bb64 diagonalAttacks = (((occupied & diagonalMask) - 2 * slider)
						 ^ bbReverse(bbReverse(occupied & diagonalMask) 
									 - 2 * bbReverse(slider)))
						 & diagonalMask;

	bb64 antiDiagonalAttacks = (((occupied & antiDiagonalMask) - 2 * slider)
							 ^ bbReverse(bbReverse(occupied & antiDiagonalMask) 
										 - 2 * bbReverse(slider)))
							 & antiDiagonalMask;

	return diagonalAttacks | antiDiagonalAttacks;
}


CandidateMoveList IcoChessEngine::getMoves()
{
	return quietMoves;
}

Position IcoChessEngine::getPosition()
{
	return pos;
}

} // End namespace IcoChess.