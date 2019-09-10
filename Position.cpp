#include <bitset>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>
#include "Move.h"
#include "IcoUtil.h"
#include "BitManipulation.h"

#include "Position.h"

bb64 Position::getEmptyBB() { return empty; }

bb64 Position::getOccupiedBB() { return occupied; }

bb64 Position::getPieceBB(pieceType piece) { return piecesBB[piece]; }
bb64 Position::getPieceBB(int piece) { return piecesBB[piece]; }

bb64 Position::getEnPassantTarget() { return enPassantTarget; }

pieceType Position::getPieceOnSquare(int square)
{
	int piece;
	for (piece = wPawns; piece <= bKing; piece++) {
		if (bbBitTest(piecesBB[piece], square))
			return pieceType(piece);
	}
	return noPiece;
}

int Position::getFiftyMoveRule() { return fiftyMoveRule; }

char Position::getCastleFlag() { return castleFlag; }

colour Position::getStm() { return m_stm; }

void Position::setSideToMove(colour side) { m_stm = side; }

std::stack<positionRecord> Position::getPositionRecord()
{
	return positionRecordSt;
}

Position::Position() {
	positionRecordSt = std::stack<positionRecord>(); m_stm = WHITE; 
	castleFlag = 0b1111; fiftyMoveRule = 0; enPassantTarget = 0; pinnedPieces = 0;
	

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
					bitboards[bRooks].set(sqNum);
					break;
				case 'n':
					bitboards[bKnights].set(sqNum);
					break;
				case 'b':
					bitboards[bBishops].set(sqNum);
					break;
				case 'q':
					bitboards[bQueens].set(sqNum);
					break;
				case 'k':
					bitboards[bKing].set(sqNum);
					break;
				case 'p':
					bitboards[bPawns].set(sqNum);
					break;
				case 'P':
					bitboards[wPawns].set(sqNum);
					break;
				case 'R':
					bitboards[wRooks].set(sqNum);
					break;
				case 'N':
					bitboards[wKnights].set(sqNum);
					break;
				case 'B':
					bitboards[wBishops].set(sqNum);
					break;
				case 'Q':
					bitboards[wQueens].set(sqNum);
					break;
				case 'K':
					bitboards[wKing].set(sqNum);
					break;
				default : break;
			}
		}
	}

	/* Convert bitsets into 64 bit bitboards */
	for (int pType = wPawns; pType <= bKing; pType++) {
		piecesBB[pType] = bitboards[pType].to_ullong();
	}
	piecesBB[wPieces]	= piecesBB[wPawns]		| piecesBB[wKnights]
						| piecesBB[wBishops]	| piecesBB[wRooks] 
						| piecesBB[wQueens]		| piecesBB[wKing];
	piecesBB[bPieces]	= piecesBB[bPawns]		| piecesBB[bKnights] 
						| piecesBB[bBishops]	| piecesBB[bRooks] 
						| piecesBB[bQueens]		| piecesBB[bKing];

	occupied			= piecesBB[wPieces]		| piecesBB[bPieces];
	empty				= ~occupied;
}

Position::Position(std::string cBoard, colour stm) {
	positionRecordSt = std::stack<positionRecord>(); m_stm = stm;
	fiftyMoveRule = 0; enPassantTarget = 0; castleFlag = 0;
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
			switch (cBoard[8 * (7-rank) + file]) {
			case 'r':
				bitboards[bRooks].set(sqNum);
				break;
			case 'n':
				bitboards[bKnights].set(sqNum);
				break;
			case 'b':
				bitboards[bBishops].set(sqNum);
				break;
			case 'q':
				bitboards[bQueens].set(sqNum);
				break;
			case 'k':
				bitboards[bKing].set(sqNum);
				break;
			case 'p':
				bitboards[bPawns].set(sqNum);
				break;
			case 'P':
				bitboards[wPawns].set(sqNum);
				break;
			case 'R':
				bitboards[wRooks].set(sqNum);
				break;
			case 'N':
				bitboards[wKnights].set(sqNum);
				break;
			case 'B':
				bitboards[wBishops].set(sqNum);
				break;
			case 'Q':
				bitboards[wQueens].set(sqNum);
				break;
			case 'K':
				bitboards[wKing].set(sqNum);
				break;
			default: break;
			}
		}
	}

	/* Convert bitsets into 64 bit bitboards */
	for (int pType = wPawns; pType <= bKing; pType++) {
		piecesBB[pType] = bitboards[pType].to_ullong();
	}
	piecesBB[wPieces] = piecesBB[wPawns] | piecesBB[wKnights]
		| piecesBB[wBishops] | piecesBB[wRooks]
		| piecesBB[wQueens] | piecesBB[wKing];
	piecesBB[bPieces] = piecesBB[bPawns] | piecesBB[bKnights]
		| piecesBB[bBishops] | piecesBB[bRooks]
		| piecesBB[bQueens] | piecesBB[bKing];

	occupied = piecesBB[wPieces] | piecesBB[bPieces];
	empty = ~occupied;
	
	/* Calculate Pinned Pieces 
	for (int pType = wPawns; pType <= bKing; pType++) {

	}*/
}

void Position::makeMove(Move move) {
	positionRecordSt.push(positionRecord(this, move));
	bool incFifty = true;

	/************************************************************
	*		If there is a capture, remove captured piece		*
	************************************************************/
	if (move.getFlags() == enPassant) {
		piecesBB[wPawns + other(m_stm)] &= ~enPassantTarget;
		incFifty = false;
	}
	else if (move.getFlags() & 0b0100) {
		bbResetBit(piecesBB[move.getCaptPiece()], move.getToSquare());
		incFifty = false;		// reset fifty move rule
	}
	
	/************************************************************
	 *		Remove piece from origin / Add to target square		*
	 ***********************************************************/
	bbResetBit(piecesBB[move.getMovPiece()], move.getFromSquare());
	if (move.getFlags() & 0b1000) { // promote piece
		switch (move.getFlags() & 0b1011) {
		case knPromo :
			bbSetBit(piecesBB[wKnights + m_stm], move.getToSquare());
			break;
		case bPromo :
			bbSetBit(piecesBB[wBishops + m_stm], move.getToSquare());
			break;
		case rPromo:
			bbSetBit(piecesBB[wRooks + m_stm], move.getToSquare());
			break;
		case qPromo:
			bbSetBit(piecesBB[wQueens + m_stm], move.getToSquare());
			break;
		}
	} else 
		bbSetBit(piecesBB[move.getMovPiece()], move.getToSquare());

	/************************************************************
	*					Update union bitboards					*
	************************************************************/
	piecesBB[wPieces + m_stm]			= piecesBB[wPawns + m_stm] 
		| piecesBB[wKnights + m_stm]	| piecesBB[wBishops + m_stm] 
		| piecesBB[wRooks + m_stm]	| piecesBB[wQueens + m_stm]
		| piecesBB[wKing + m_stm];
	occupied = piecesBB[wPieces] | piecesBB[bPieces];
	empty = ~occupied;

	/************************************************************
	* Special case for pawn moves:								*
	*		reset fifty move rule and set en passant target		*
	************************************************************/
	enPassantTarget = 0;		// reset en passant target
	if (move.getMovPiece() == wPawns || move.getMovPiece() == bPawns) {
		incFifty = false;		// reset fifty move rule
		if (move.getFlags() == dblPawnPush) {
			bbSetBit(enPassantTarget, move.getToSquare());
		}
	}

	m_stm = other(m_stm);						// Update side to move
	if (incFifty) fiftyMoveRule += 1;		// Inc fifty move rule
	else fiftyMoveRule = 0;
}

void Position::unmakeMove() {
	positionRecord rec = positionRecordSt.top();
	positionRecordSt.pop();

	/************************************************************
	*		If there was a capture, replace captured piece		*
	************************************************************/
	pieceType captPiece = rec.getPrevMove().getCaptPiece();
	if (captPiece != noPiece) {
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
	enPassantTarget = rec.getEnPassantTarget();
	m_stm = other(m_stm);

	/************************************************************
	*					Update union bitboards					*
	************************************************************/
	piecesBB[wPieces + m_stm] = piecesBB[wPawns + m_stm]
		| piecesBB[wKnights + m_stm] | piecesBB[wBishops + m_stm]
		| piecesBB[wRooks + m_stm] | piecesBB[wQueens + m_stm]
		| piecesBB[wKing + m_stm];
	occupied = piecesBB[wPieces] | piecesBB[bPieces];
	empty = ~occupied;
}

/***************************************************************
*/
positionRecord::positionRecord(Position* pos, Move move) {
	prevMove = move;
	fiftyMoveRule = pos->getFiftyMoveRule();
	enPassantTarget = pos->getEnPassantTarget();
}

void positionRecord::setPrevMove(Move move) { prevMove = move; }

void positionRecord::setFiftyMoveRule(int ply) 
{ fiftyMoveRule = ply; }

void positionRecord::setEnPassantTarget(bb64 target) 
{ enPassantTarget = target; }

Move positionRecord::getPrevMove() { return prevMove; }

int positionRecord::getFiftyMoveRule() { return fiftyMoveRule; }

bb64 positionRecord::getEnPassantTarget() { return enPassantTarget; }
