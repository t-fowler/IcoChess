#pragma once
#ifndef MOVE_H
#define MOVE_H

class Position;
enum pieceType;
/****************************************************************
*		The move class encodes a chess move into a 16 bit		*
*	integer. 6 bits each to encode the square index of the		*
*	origin and target squares of the piece. 4 bits as a flag to *
*	represent different possible types of moves.				*
****************************************************************/
class Move
{
private:
	unsigned short move;
	pieceType movPiece;
	pieceType captPiece;
public:
	/************** Constructors and Destructors ***************/

	/************************************************************
	*		This constructor creates a move with the requested	*
	*	to and from squares. The given flags should be accurate	*
	*	to the type of move being created.						*
	*															*
	*	@unsigned int fromSquare -- the square containing the	*
	*							piece being moved.				*		*
	*	@unsigned int toSquare	 -- the target square			*
	*	@unsigned int flags		 -- the type of move			*
	************************************************************/
	Move(unsigned int fromSquare,
			unsigned int toSquare,
				unsigned int flags);
	Move(Position * pos,
		unsigned int fromSquare,
			unsigned int toSquare,
				unsigned int flags);
	Move();
	~Move();

	/******************** Setters and Getters ******************/
	void setToSquare(unsigned int toSquare);
	void setFromSquare(unsigned int fromSquare);
	void setFlags(unsigned int flags);
	void setMovPiece(pieceType piece);
	void setCaptPiece(pieceType piece);
	pieceType getMovPiece();
	pieceType getCaptPiece();
	int getToSquare();
	int getFromSquare();
	int getFlags();
	short getMove();

	/********************* Member Functions ********************/
	bool isEqual(Move other);
};

#endif	// Inclusion guard
