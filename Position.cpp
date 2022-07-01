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

void Position::setUnionBitboards()
{
	piecesBB[W_PIECE] = piecesBB[W_PAWN] | piecesBB[W_KNIGHT]
		| piecesBB[W_BISHOP] | piecesBB[W_ROOK]
		| piecesBB[W_QUEEN] | piecesBB[W_KING];

	piecesBB[B_PIECE] = piecesBB[B_PAWN] | piecesBB[B_KNIGHT]
		| piecesBB[B_BISHOP] | piecesBB[B_ROOK]
		| piecesBB[B_QUEEN] | piecesBB[B_KING];

	occupied = piecesBB[W_PIECE] | piecesBB[B_PIECE];
	empty = ~occupied;
}

bb64 Position::getEmptyBB() { return empty; }

bb64 Position::getOccupiedBB() { return occupied; }

bb64 Position::getPieceBB(pieceType piece) { return piecesBB[piece]; }
bb64 Position::getPieceBB(int piece) { return piecesBB[piece]; }

bb64 Position::getEnPassantTarget() { return enPassantTarget; }

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
	castleFlag = 0b1111; fiftyMoveRule = 0; enPassantTarget = 0;


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
	
	setUnionBitboards();
}

Position::Position(std::string cBoard, colour stm)
{
	positionRecordSt = std::vector<positionRecord>(); 
	m_stm = stm;
	fiftyMoveRule = 0; 
	enPassantTarget = 0; 
	castleFlag = 0;
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
	
	setUnionBitboards();
}

Position::Position(std::string fen)
{
	positionRecordSt = std::vector<positionRecord>();

	for (pieceType pt = W_PAWN; pt <= B_KING; pt = (pieceType)(pt + 1)) {
		piecesBB[pt] = 0ULL;
	}

	size_t delim = std::string::npos;
	for (int rank = 7; rank >= 0; rank--) {
		delim = fen.find("/");
		if (delim == std::string::npos) {
			delim = fen.find(" ");
		}
		int file = 0;
		std::string rankString = fen.substr(0, delim);
		fen.erase(0, delim + 1);

		for (auto ch : rankString) {
			switch (ch) {
			case 'p':
				piecesBB[B_PAWN] |= 1ULL << (8 * rank + file);
				break;
			case 'P':
				piecesBB[W_PAWN] |= 1ULL << (8 * rank + file);
				break;
			case 'n':
				piecesBB[B_KNIGHT] |= 1ULL << (8 * rank + file);
				break;
			case 'N':
				piecesBB[W_KNIGHT] |= 1ULL << (8 * rank + file);
				break;
			case 'b':
				piecesBB[B_BISHOP] |= 1ULL << (8 * rank + file);
				break;
			case 'B':
				piecesBB[W_BISHOP] |= 1ULL << (8 * rank + file);
				break;
			case 'r':
				piecesBB[B_ROOK] |= 1ULL << (8 * rank + file);
				break;
			case 'R':
				piecesBB[W_ROOK] |= 1ULL << (8 * rank + file);
				break;
			case 'q':
				piecesBB[B_QUEEN] |= 1ULL << (8 * rank + file);
				break;
			case 'Q':
				piecesBB[W_QUEEN] |= 1ULL << (8 * rank + file);
				break;
			case 'k':
				piecesBB[B_KING] |= 1ULL << (8 * rank + file);
				break;
			case 'K':
				piecesBB[W_KING] |= 1ULL << (8 * rank + file);
				break;
			case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8':
				file += ch - '1';
				break;
			}
			file++;
		}
	}

	setUnionBitboards();

	if (fen[0] == 'w') {
		m_stm = WHITE;
	}
	else if (fen[0] == 'b') {
		m_stm = BLACK;
	}
	fen.erase(0, 2);

	castleFlag = 0;
	if (fen[0] != '-') {
		int i = 0;
		while (fen[i] != ' ') {
			switch (fen[i++]) {
			case 'K':
				castleFlag |= 0b1000;
				break;
			case 'k':
				castleFlag |= 0b0010;
				break;
			case 'Q':
				castleFlag |= 0b0100;
				break;
			case 'q':
				castleFlag |= 0b0001;
				break;
			}
		}
		fen.erase(0, i+1);
		
	}
	else {
		fen.erase(0, 2);
	}

	if (fen[0] != '-') {
		int rank = fen[0] - 'a';
		int file = fen[1] - '1';
		enPassantTarget = 1ULL << (8 * rank + file);
		fen.erase(0, 3);
	}
	else {
		fen.erase(0, 2);
	}

	if (fen[1] != ' ') {
		fiftyMoveRule = std::stoi(fen.substr(0, 2));
		fen.erase(0, 3);
	}
	else {
		fiftyMoveRule = std::stoi(fen.substr(0, 1));
		fen.erase(0, 2);
	}

	// TODO: Implement fullmove counter.
	
}


void Position::makeMove(Move move)
{
	positionRecordSt.push_back(positionRecord(this, move));
	bool incFifty = true;

	// Remove possible captured piece.
	if (move.getFlags() == EN_PASSANT) {
		piecesBB[move.getCaptPiece()] &= ~enPassantTarget;
		incFifty = false;		// reset fifty move rule.
	}
	else if (move.getFlags() & 0b0100) {
		bbResetBit(piecesBB[move.getCaptPiece()], move.getToSquare());
		incFifty = false;		// reset fifty move rule.
	}

	// Update bitboards.
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

	setUnionBitboards();

	// Special case for pawn moves:
	// reset fifty move rule and set en passant target
	enPassantTarget = 0;		// reset en passant target
	if (move.getMovPiece() == W_PAWN || move.getMovPiece() == B_PAWN) {
		incFifty = false;		// reset fifty move rule
		if (move.getFlags() == DOUBLE_PAWN_PUSH) {
			bbSetBit(enPassantTarget, move.getToSquare());
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

	// Replace possible captured piece.
	pieceType captPiece = rec.getPrevMove().getCaptPiece();
	if (captPiece != NO_PIECE) {
		bbSetBit(piecesBB[captPiece], rec.getPrevMove().getToSquare());
	}

	// Remove piece from target / Add to origin square
	pieceType movPiece = rec.getPrevMove().getMovPiece();
	bbResetBit(piecesBB[movPiece], rec.getPrevMove().getToSquare());
	bbSetBit(piecesBB[movPiece], rec.getPrevMove().getFromSquare());

	// Reset fifty move rule / en passant target / stm
	fiftyMoveRule = rec.getFiftyMoveRule();
	enPassantTarget = rec.getEnPassantTarget();
	m_stm = other(m_stm);

	
	// Update union bitboards
	setUnionBitboards();
}

positionRecord::positionRecord(Position* pos, Move move)
{
	prevMove = move;
	fiftyMoveRule = pos->getFiftyMoveRule();
	enPassantTarget = pos->getEnPassantTarget();
}

void positionRecord::setPrevMove(Move move) { prevMove = move; }

void positionRecord::setFiftyMoveRule(int ply)
{
	fiftyMoveRule = ply;
}

void positionRecord::setenPassantTarget(bb64 target)
{
	enPassantTarget = target;
}

Move positionRecord::getPrevMove() { return prevMove; }

int positionRecord::getFiftyMoveRule() { return fiftyMoveRule; }

bb64 positionRecord::getEnPassantTarget() { return enPassantTarget; }

}