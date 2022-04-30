#include <bitset>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>

#include "Move.h"
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"

namespace IcoChess
{

bb64 Position::getEmptyBB() { return empty; }

bb64 Position::getOccupiedBB() { return occupied; }

bb64 Position::getPieceBB(pieceType piece) { return piecesBB[piece]; }
bb64 Position::getPieceBB(int piece) { return piecesBB[piece]; }

bb64 Position::getEN_PASSANTTarget() { return EN_PASSANTTarget; }

pieceType Position::getPieceOnSquare(int square)
{
	int piece;
	for (piece = W_PAWN; piece <= B_KING; piece++) {
		if (bbBitTest(piecesBB[piece], square))
			return pieceType(piece);
	}
	return NO_PIECE;
}

int Position::getFiftyMoveRule() { return fiftyMoveRule; }

char Position::getCastleFlag() { return castleFlag; }

colour Position::getStm() { return m_stm; }

void Position::setSideToMove(colour side) { m_stm = side; }

std::vector<positionRecord> Position::getPositionRecord()
{
	return positionRecordSt;
}

Position::Position()
{
	positionRecordSt = std::vector<positionRecord>(); m_stm = WHITE;
	castleFlag = 0b1111; fiftyMoveRule = 0; EN_PASSANTTarget = 0;


	/* A visual representation of the desired start position */
	std::string cBoard[8] =
	{
		"r n b q k b n r",
		"p p p p p p p p",
		"_ _ _ _ _ _ _ _",
		"_ _ _ _ _ _ _ _",
		"_ _ _ _ _ _ _ _",
		"_ _ _ _ _ _ _ _",
		"P P P P P P P P",
		"R N B Q K B N R"
	};


	/* Initialize bitsets for building bitboards */
	std::bitset<64> bitboards[12];
	for (int i = 0; i < 12; i++) {
		bitboards[i] = std::bitset<64>();
	}

	/* Iterate through chess board string and set the	*
	 * appropriate bits in the bitset for each piece	*/
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file <= 14; file += 2) {
			int sqNum = 8 * rank + file / 2;
			switch (cBoard[7 - rank][file]) {
			case 'r':
				bitboards[B_ROOK].set(sqNum);
				break;
			case 'n':
				bitboards[B_KNIGHT].set(sqNum);
				break;
			case 'b':
				bitboards[B_BISHOP].set(sqNum);
				break;
			case 'q':
				bitboards[B_QUEEN].set(sqNum);
				break;
			case 'k':
				bitboards[B_KING].set(sqNum);
				break;
			case 'p':
				bitboards[B_PAWN].set(sqNum);
				break;
			case 'P':
				bitboards[W_PAWN].set(sqNum);
				break;
			case 'R':
				bitboards[W_ROOK].set(sqNum);
				break;
			case 'N':
				bitboards[W_KNIGHT].set(sqNum);
				break;
			case 'B':
				bitboards[W_BISHOP].set(sqNum);
				break;
			case 'Q':
				bitboards[W_QUEEN].set(sqNum);
				break;
			case 'K':
				bitboards[W_KING].set(sqNum);
				break;
			default: break;
			}
		}
	}

	/* Convert bitsets into 64 bit bitboards */
	for (int pType = W_PAWN; pType <= B_KING; pType++) {
		piecesBB[pType] = bitboards[pType].to_ullong();
	}
	piecesBB[W_PIECE] = piecesBB[W_PAWN] | piecesBB[W_KNIGHT]
		| piecesBB[W_BISHOP] | piecesBB[W_ROOK]
		| piecesBB[W_QUEEN] | piecesBB[W_KING];
	piecesBB[B_PIECE] = piecesBB[B_PAWN] | piecesBB[B_KNIGHT]
		| piecesBB[B_BISHOP] | piecesBB[B_ROOK]
		| piecesBB[B_QUEEN] | piecesBB[B_KING];

	occupied = piecesBB[W_PIECE] | piecesBB[B_PIECE];
	empty = ~occupied;
}

Position::Position(std::string cBoard, colour stm)
{
	positionRecordSt = std::vector<positionRecord>(); m_stm = stm;
	fiftyMoveRule = 0; EN_PASSANTTarget = 0; castleFlag = 0;
	if (cBoard[8 * 0 + 4] == 'k') { // king is on e8
		if (cBoard[8 * 0 + 0] == 'r') // rook is on a8
			castleFlag |= 0b0001;
		if (cBoard[8 * 0 + 7] == 'r') // rook is on h8
			castleFlag |= 0b0010;
	}
	if (cBoard[8 * 7 + 4] == 'K') { // king is on e1
		if (cBoard[8 * 7 + 0] == 'R') // rook is on a1
			castleFlag |= 0b0100;
		if (cBoard[8 * 7 + 7] == 'R') // rook is on h1
			castleFlag |= 0b1000;
	}

	/* Initialize bitsets for building bitboards */
	std::bitset<64> bitboards[12];
	for (int i = 0; i < 12; i++) {
		bitboards[i] = std::bitset<64>();
	}

	/* Iterate through chess board string and set the	*
	 * appropriate bits in the bitset for each piece	*/
	for (int rank = 7; rank >= 0; rank--) {
		for (int file = 7; file >= 0; file--) {
			int sqNum = 8 * rank + file;
			switch (cBoard[8 * (7 - rank) + file]) {
			case 'r':
				bitboards[B_ROOK].set(sqNum);
				break;
			case 'n':
				bitboards[B_KNIGHT].set(sqNum);
				break;
			case 'b':
				bitboards[B_BISHOP].set(sqNum);
				break;
			case 'q':
				bitboards[B_QUEEN].set(sqNum);
				break;
			case 'k':
				bitboards[B_KING].set(sqNum);
				break;
			case 'p':
				bitboards[B_PAWN].set(sqNum);
				break;
			case 'P':
				bitboards[W_PAWN].set(sqNum);
				break;
			case 'R':
				bitboards[W_ROOK].set(sqNum);
				break;
			case 'N':
				bitboards[W_KNIGHT].set(sqNum);
				break;
			case 'B':
				bitboards[W_BISHOP].set(sqNum);
				break;
			case 'Q':
				bitboards[W_QUEEN].set(sqNum);
				break;
			case 'K':
				bitboards[W_KING].set(sqNum);
				break;
			default: break;
			}
		}
	}

	/* Convert bitsets into 64 bit bitboards */
	for (int pType = W_PAWN; pType <= B_KING; pType++) {
		piecesBB[pType] = bitboards[pType].to_ullong();
	}
	piecesBB[W_PIECE] = piecesBB[W_PAWN] | piecesBB[W_KNIGHT]
		| piecesBB[W_BISHOP] | piecesBB[W_ROOK]
		| piecesBB[W_QUEEN] | piecesBB[W_KING];

	piecesBB[B_PIECE] = piecesBB[B_PAWN] | piecesBB[B_KNIGHT]
		| piecesBB[B_BISHOP] | piecesBB[B_ROOK]
		| piecesBB[B_QUEEN] | piecesBB[B_KING];

	occupied = piecesBB[W_PIECE] | piecesBB[B_PIECE];
	empty = ~occupied;
}

void Position::makeMove(Move move)
{
	positionRecordSt.push_back(positionRecord(this, move));
	bool incFifty = true;

	/************************************************************
	*		If there is a CAPTURE, remove CAPTUREd piece		*
	************************************************************/
	if (move.getFlags() == EN_PASSANT) {
		piecesBB[move.getCaptPiece()] &= ~EN_PASSANTTarget;
		incFifty = false;		// reset fifty move rule.
	}
	else if (move.getFlags() & 0b0100) {
		bbResetBit(piecesBB[move.getCaptPiece()], move.getToSquare());
		incFifty = false;		// reset fifty move rule.
	}

	/************************************************************
	 *		Remove piece from origin / Add to target square		*
	 ***********************************************************/
	bbResetBit(piecesBB[move.getMovPiece()], move.getFromSquare());
	if (move.getFlags() & 0b1000) { // promote piece
		switch (move.getFlags() & 0b1011) {
		case PROMOTE_TO_KNIGHT:
			bbSetBit(piecesBB[W_KNIGHT + m_stm], move.getToSquare());
			break;
		case PROMOTE_TO_BISHOP:
			bbSetBit(piecesBB[W_BISHOP + m_stm], move.getToSquare());
			break;
		case PROMOTE_TO_ROOK:
			bbSetBit(piecesBB[W_ROOK + m_stm], move.getToSquare());
			break;
		case PROMOTE_TO_QUEEN:
			bbSetBit(piecesBB[W_QUEEN + m_stm], move.getToSquare());
			break;
		}
	}
	else {
		bbSetBit(piecesBB[move.getMovPiece()], move.getToSquare());
	}

	/************************************************************
	*					Update union bitboards					*
	************************************************************/
	piecesBB[W_PIECE] = piecesBB[W_KING] | piecesBB[W_PAWN]
		| piecesBB[W_KNIGHT] | piecesBB[W_BISHOP]
		| piecesBB[W_ROOK] | piecesBB[W_QUEEN];
	piecesBB[B_PIECE] = piecesBB[B_KING] | piecesBB[B_PAWN]
		| piecesBB[B_KNIGHT] | piecesBB[B_BISHOP]
		| piecesBB[B_ROOK] | piecesBB[B_QUEEN];
	occupied = piecesBB[W_PIECE] | piecesBB[B_PIECE];
	empty = ~occupied;

	/************************************************************
	* Special case for pawn moves:								*
	*		reset fifty move rule and set en passant target		*
	************************************************************/
	EN_PASSANTTarget = 0;		// reset en passant target
	if (move.getMovPiece() == W_PAWN || move.getMovPiece() == B_PAWN) {
		incFifty = false;		// reset fifty move rule
		if (move.getFlags() == DOUBLE_PAWN_PUSH) {
			bbSetBit(EN_PASSANTTarget, move.getToSquare());
		}
	}

	m_stm = other(m_stm);						// Update side to move
	if (incFifty) fiftyMoveRule += 1;		// Inc fifty move rule
	else fiftyMoveRule = 0;
}

void Position::unmakeMove()
{
	positionRecord rec = positionRecordSt.back();
	positionRecordSt.pop_back();

	/************************************************************
	*		If there was a CAPTURE, replace CAPTUREd piece		*
	************************************************************/
	pieceType captPiece = rec.getPrevMove().getCaptPiece();
	if (captPiece != NO_PIECE) {
		bbSetBit(piecesBB[captPiece], rec.getPrevMove().getToSquare());
	}

	/************************************************************
	*		Remove piece from target / Add to origin square		*
	************************************************************/
	pieceType movPiece = rec.getPrevMove().getMovPiece();
	bbResetBit(piecesBB[movPiece], rec.getPrevMove().getToSquare());
	bbSetBit(piecesBB[movPiece], rec.getPrevMove().getFromSquare());

	/************************************************************
	*		Reset fifty move rule / en passant target / stm		*
	************************************************************/
	fiftyMoveRule = rec.getFiftyMoveRule();
	EN_PASSANTTarget = rec.getEN_PASSANTTarget();
	m_stm = other(m_stm);

	/************************************************************
	*					Update union bitboards					*
	************************************************************/
	piecesBB[W_PIECE + m_stm] = piecesBB[W_PAWN + m_stm]
		| piecesBB[W_KNIGHT + m_stm] | piecesBB[W_BISHOP + m_stm]
		| piecesBB[W_ROOK + m_stm] | piecesBB[W_QUEEN + m_stm]
		| piecesBB[W_KING + m_stm];
	occupied = piecesBB[W_PIECE] | piecesBB[B_PIECE];
	empty = ~occupied;
}

/***************************************************************
*/
positionRecord::positionRecord(Position* pos, Move move)
{
	prevMove = move;
	fiftyMoveRule = pos->getFiftyMoveRule();
	EN_PASSANTTarget = pos->getEN_PASSANTTarget();
}

void positionRecord::setPrevMove(Move move) { prevMove = move; }

void positionRecord::setFiftyMoveRule(int ply)
{
	fiftyMoveRule = ply;
}

void positionRecord::setEN_PASSANTTarget(bb64 target)
{
	EN_PASSANTTarget = target;
}

Move positionRecord::getPrevMove() { return prevMove; }

int positionRecord::getFiftyMoveRule() { return fiftyMoveRule; }

bb64 positionRecord::getEN_PASSANTTarget() { return EN_PASSANTTarget; }

}