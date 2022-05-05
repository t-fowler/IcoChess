#include <iostream>
#include "stdlib.h"

#include "Move.h"
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"

namespace IcoChess
{

void Move::setToSquare(unsigned int toSquare)
{
	if (toSquare > 0x3F) {
		std::cerr << "Error setting TO SQUARE in MOVE."
			<< " TO SQUARE OUT OF BOUNDS." << std::endl;
		exit(EXIT_FAILURE);
	}
	move |= (toSquare << 4);
}

void Move::setFromSquare(unsigned int fromSquare)
{
	if (fromSquare > 0x3F) {
		std::cerr << "Error setting FROM SQUARE in MOVE."
			<< " FROM SQUARE OUT OF BOUNDS." << std::endl;
		exit(EXIT_FAILURE);
	}
	move |= (fromSquare << 10);
}

void Move::setFlags(unsigned int flags)
{
	if (flags > 0xF) {
		std::cerr << "Error setting FLAGS in MOVE."
			<< " FLAGS OUT OF BOUNDS." << std::endl;
		exit(EXIT_FAILURE);
	}
	move |= flags;
}

void Move::setMovPiece(pieceType piece) { movPiece = piece; }

void Move::setCaptPiece(pieceType piece) { captPiece = piece; }

pieceType Move::getMovPiece() { return movPiece; }

pieceType Move::getCaptPiece() { return captPiece; }

int Move::getToSquare() { return (move >> 4) & 0x3F; }

int Move::getFromSquare() { return (move >> 10); }

int Move::getFlags() { return move & 0xF; }

short Move::getMove() { return move; }

bool Move::isEqual(Move other)
{
	if (this->getMovPiece() == other.getMovPiece()
		&& this->getCaptPiece() == other.getCaptPiece()
		&& this->getMove() == other.getMove())
		return true;
	return false;
}

std::string Move::toString()
{
	std::string str = "";
	char pFile;


	switch (getFromSquare() % 8) {
	case 0:
		pFile = 'a';
		break;
	case 1:
		pFile = 'b';
		break;
	case 2:
		pFile = 'c';
		break;
	case 3:
		pFile = 'd';
		break;
	case 4:
		pFile = 'e';
		break;
	case 5:
		pFile = 'f';
		break;
	case 6:
		pFile = 'g';
		break;
	case 7:
		pFile = 'h';
		break;
	}

	switch (movPiece) {
	case W_PAWN:
	case B_PAWN:
		if (getCaptPiece() != NO_PIECE) {
			switch (getFromSquare() % 8) {
			case 0:
				pFile = 'a';
				break;
			case 1:
				pFile = 'b';
				break;
			case 2:
				pFile = 'c';
				break;
			case 3:
				pFile = 'd';
				break;
			case 4:
				pFile = 'e';
				break;
			case 5:
				pFile = 'f';
				break;
			case 6:
				pFile = 'g';
				break;
			case 7:
				pFile = 'h';
				break;
			}

			str += pFile;
		}
		break;
	case W_BISHOP:
	case B_BISHOP:
		str += "B";
		break;
	case W_KNIGHT:
	case B_KNIGHT:
		str += "N";
		break;
	case W_ROOK:
	case B_ROOK:
		str += "R";
		break;
	case W_QUEEN:
	case B_QUEEN:
		str += "Q";
		break;
	case W_KING:
	case B_KING:
		str += "K";
		break;
	}

	if (getCaptPiece() != NO_PIECE) {
		str += 'x';
	}

	switch (getToSquare() % 8) {
	case 0:
		str += 'a';
		break;
	case 1:
		str += 'b';
		break;
	case 2:
		str += 'c';
		break;
	case 3:
		str += 'd';
		break;
	case 4:
		str += 'e';
		break;
	case 5:
		str += 'f';
		break;
	case 6:
		str += 'g';
		break;
	case 7:
		str += 'h';
		break;
	}

	switch (getToSquare() / 8) {
	case 0:
		str += '1';
		break;
	case 1:
		str += '2';
		break;
	case 2:
		str += '3';
		break;
	case 3:
		str += '4';
		break;
	case 4:
		str += '5';
		break;
	case 5:
		str += '6';
		break;
	case 6:
		str += '7';
		break;
	case 7:
		str += '8';
		break;
	}

	return str;
}

Move::Move(unsigned int fromSquare,
		   unsigned int toSquare,
		   unsigned int flags)
{
	move = 0;
	setFromSquare(fromSquare);
	setToSquare(toSquare);
	setFlags(flags);
}

Move::Move(Position& pos,
		   unsigned int fromSquare,
		   unsigned int toSquare,
		   unsigned int flags)
{
	move = 0;
	setFromSquare(fromSquare);
	setToSquare(toSquare);
	setFlags(flags);
	movPiece = pos.getPieceOnSquare(fromSquare);
	if (flags == EN_PASSANT) {
		captPiece = pieceType(W_PAWN + other(pos.getStm()));
	}
	else {
		captPiece = pos.getPieceOnSquare(toSquare);
	}
}

Move::Move()
{
	move = 0;
	movPiece = W_PAWN;
	captPiece = NO_PIECE;
}

Move::~Move()
{}


CandidateMoveList::CandidateMoveList()
{
}

CandidateMoveList::~CandidateMoveList()
{}

CandidateMoveList::CandidateMoveList(Move h)
{
	moveList.push_back(h);
}

void CandidateMoveList::add(Move newMove)
{
	moveList.push_back(newMove);
}

void CandidateMoveList::remove(int index)
{
	moveList.erase(moveList.begin() + index);
}

bool CandidateMoveList::contains(Move move)
{
	for (int i = 0; i < getSize(); i++) {
		if (moveList[i].isEqual(move))
			return true;
	}
	return false;
}

int CandidateMoveList::getSize() { return moveList.size(); }

Move CandidateMoveList::getMove(int index) { return moveList[index]; }

}