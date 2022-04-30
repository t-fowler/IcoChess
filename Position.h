#pragma once
#ifndef POSITION_H
#define POSITION_H
#include <vector>
#include "Move.h"
#include "IcoUtil.h"

namespace IcoChess
{

/********************************************************************
*		The positionRecord class is to keep track of certain        *
*	position specific variables after moves are made. This			*
*	is so that the position can be reverted to an earlier			*
*	state. Kept in a stack so as to allow multiple unmakes			*
********************************************************************/
class positionRecord
{
private:
	Move prevMove;			// The move that was made
	int fiftyMoveRule;		// Half move clock before the move
	bb64 EN_PASSANTTarget;	// If there was an EN_PASSANTTarget

public:
	/****************************************************************
	*		The constructor creates a record of the position		*
	*	given as a parameter.										*
	*																*
	*	@param Position* pos		-- The position to create a		*
	*							a record of. Provided as a			*
	*							reference so as to use in a stack  	*
	*	@param Move move			-- The move made at the current *
	*							position (whose record is taken)	*
	*****************************************************************/
	positionRecord(Position* pos, Move move);

	/************************************************************
	*					  Setters and Getters					*
	************************************************************/
	void setPrevMove(Move move);
	void setFiftyMoveRule(int ply);
	void setEN_PASSANTTarget(bb64 target);

	Move getPrevMove();
	int getFiftyMoveRule();
	bb64 getEN_PASSANTTarget();
};

/********************************************************************
 *		The chess position comprises of a number of 64 bit			*
 *	integers which are sets, called bitboards, that encapsulate		*
 *	a particular property of the chessboard. Each bit represents	*
 *	one of the 64 squares on the board. For example, there are 2	*
 *	bitboards -- one for each colour -- for each of the pieces		*
 *	in the game. A one bit would represent the existance of a		*
 *	piece of that type, with the bit index representing the			*
 *	square that it is on.											*
 *																	*
 *	Member Variables												*
 *	-----------------												*
 *																	*
 *	piecesBB[]	-- an array containing bitboards for each piece		*
 *			and colour combination. The last 2 elements are	a		*
 *			union of all the white and black pieces respectively	*
 *	occupied	-- the set of all occupied squares					*
 *	empty		-- the set of all empty squares						*
 *	EN_PASSANTTarget		-- the set of all pawns that can be taken	*
					en passant. Usually set to 0					*
 *  positionRecordSt	-- A stack of positionRecords that keep		*
 *					track of certain aspects of the game			*
 *	stm			-- the side to move									*
 *	fiftyMoveRule		-- a clock that tracks the progress of		*
 *					the fifty move rule								*
 ********************************************************************/
class Position
{
private:
	std::vector<positionRecord> positionRecordSt;
	colour m_stm;				// Side to move: 0 = white, 1 = black
	char castleFlag;		// white kingside/queenside then black
	int fiftyMoveRule;
	bb64 piecesBB[14];
	bb64 occupied;
	bb64 empty;
	bb64 EN_PASSANTTarget;


public:
	/*********************** Constructors **********************/

	/************************************************************
	*		The default constructor creates the standard		*
	*	starting position. It can also be used for testing		*
	*	purposes by altering the chessboard string inside the	*
	*	constructor.											*
	************************************************************/
	Position();

	/************************************************************
	*		This constructor creates a chess position of the	*
	*	string input. The string should be in the following		*
	*	format.													*
	*	std::string cBoard =									*													*
	* 	"rnbqkbnr" +											*
	*	"pppppppp" +											*
	*	"________" +											*
	*	"________" +											*
	*	"________" +											*
	*	"________" +											*
	*	"PPPPPPPP" +											*
	*	"RNBQKBNR"												*
	************************************************************/
	Position(std::string cBoard, colour stm);

	// Copy Constructor
	//Position(const Position& pos);

	// Move Assignment
	//Position operator=(const Position& post);

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
	bb64 getPieceBB(int);
	bb64 getEN_PASSANTTarget();		// returns target square for enP
	pieceType getPieceOnSquare(int square);
	int getFiftyMoveRule();
	char getCastleFlag();
	colour getStm();
	void setSideToMove(colour stm);	// sets the side to move
	std::vector<positionRecord> getPositionRecord();


};

}
#endif		// Inclusion guard