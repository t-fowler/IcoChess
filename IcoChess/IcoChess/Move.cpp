#include "Move.h"
#include "stdlib.h"
#include <iostream>
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"

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

int Move::getToSquare(){ return (move >> 4) & 0x3F; }

int Move::getFromSquare() { return (move >> 10); }

int Move::getFlags(){ return move & 0xF; }

short Move::getMove() { return move; }

bool Move::isEqual(Move other)
{
	if (this->getMovPiece() == other.getMovPiece()
		&& this->getCaptPiece() == other.getCaptPiece()
		&& this->getMove() == other.getMove())
		return true;
	return false;
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

Move::Move(Position* pos,
			unsigned int fromSquare,
				unsigned int toSquare,
					unsigned int flags)
{
	move = 0;
	setFromSquare(fromSquare);
	setToSquare(toSquare);
	setFlags(flags);
	movPiece = pos->getPieceOnSquare(fromSquare);
	if (flags == enPassant) 
			captPiece = pieceType(wPawns + other(pos->getStm()));
	else	captPiece = pos->getPieceOnSquare(toSquare);
}

Move::Move()
{
}

Move::~Move()
{
}
