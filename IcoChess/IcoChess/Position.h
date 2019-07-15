#pragma once
#ifndef POSITION_H
#define POSITION_H
#include <stack>
#include "Move.h"
/************************************************************
*		The positionRecord class is to keep track of certain*
*	position specific variables after moves are made. This	*
*	is so that the position can be reverted to an earlier	*
*	state. Kept in a stack so as to allow multiple unmakes	*
************************************************************/
class positionRecord
{
private:
	Move prevMove;			// The move that was made
	int fiftyMoveRule;		// Half move clock before the move
	bb64 enPassantTarget;	// If there was an enPassantTarget

public:
	/************************************************************
	*		The constructor creates a record of the position	*
	*	given as a parameter.									*
	*															*
	*	@param Position pos		-- The position to create a		*
	*							a record of.					*
	************************************************************/
	positionRecord(Position* pos, Move move);

	/************************************************************
	*					  Setters and Getters					*
	************************************************************/
	void setPrevMove(Move move);
	void setFiftyMoveRule(int ply);
	void setEnPassantTarget(bb64 target);

	Move getPrevMove();
	int getFiftyMoveRule();
	bb64 getEnPassantTarget();
};

/****************************************************************
 *		The chess position comprises of a number of 64 bit		*
 *	integers which are sets, called bitboards, that encapsulate	*
 *	a particular property of the chessboard. Each bit represents*
 *	one of the 64 squares on the board. For example, there are 2*
 *	bitboards -- one for each colour -- for each of the pieces	*
 *	in the game. A one bit would represent the existance of a	*
 *	piece of that type, with the bit index representing the		*
 *	square that it is on.										*
 *																*
 *	piecesBB[]	-- an array containing bitboards for each piece	*
 *			and colour combination. The last 2 elements are	a	*
 *			union of all the white and black pieces respectively*
 *	occupied	-- the set of all occupied squares				*
 *	empty		-- the set of all empty squares					*
 *	pieceType	-- an enumeration used for accessing the correct*
 *			index of the piecesBB array.						*
 ***************************************************************/
class Position
{
private:
	std::stack<positionRecord> positionRecordSt;
	colour stm;				// Side to move: 0 = white, 1 = black
	char castleFlag;		// white kingside/queenside then black
	int fiftyMoveRule;
	bb64 piecesBB[14];
	bb64 occupied;
	bb64 empty;
	bb64 enPassantTarget;


public:
	/*********************** Constructors **********************/

	/************************************************************
	*		The default constructor creates the standard		*
	*	starting position. It can also be used for testing		*
	*	purposes by altering the chessboard string inside the	*
	*	constructor.											*
	************************************************************/
	Position();

	/********************** Member Methods *********************/
	
	/*************************************************************
	*		The makeMove function updates all bitboards and		 *
	*	other position specific variables to reflect the new	 *
	*	position after the move is made.						 *
	*															 *
	*	@Move move	- A legal chess move with the proper flags	 *
	*			attributed to it. En passant move squares should *
	*			be the actual squares the pawn is moving too.	 *
	*************************************************************/
	void makeMove(Move move);

	/*************************************************************
	*		The unmakeMove function reverses all bitboards and	 *
	*	other position specific variables to reflect the previous*
	*	position before the last move was made. It is the inverse*
	*	of the makeMove function.								 *
	*															 *
	*	@Move move	- A legal chess move with the proper flags	 *
	*			attributed to it. En passant move squares should *
	*			be the actual squares the pawn is moving too.	 *
	*************************************************************/
	void unmakeMove();

	/******************* Setters and Getters *******************/
	bb64 getEmptyBB();				// returns empty
	bb64 getOccupiedBB();			// returns occupied 
	bb64 getPieceBB(pieceType);	// returns requested piece BB
	bb64 getEnPassantTarget();		// returns target square for enP
	pieceType getPieceOnSquare(int square);
	int getFiftyMoveRule();
	char getCastleFlag();
	colour getStm();
	void setSideToMove(colour stm);	// sets the side to move
	std::stack<positionRecord> getPositionRecord();

	
};

#endif		// Inclusion guard