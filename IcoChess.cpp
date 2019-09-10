class Position;
#include <iostream>
#include <stack>
#include "stdlib.h"
#include "Move.h"
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"
#include "IcoMoveGenerator.h"

void testMsb() {
	bb64 bb = 0;
	if (msb(bb) != (unsigned long long) -1) std::cout << "Test 1: wrong index at 0." << std::endl;
	for (int i = 1; i < 63; i++) {
		bb = (1ULL << i);
		if (msb(bb) != 1ULL << (i + 1)) {
			std::cout << "Test 1: wrong index at " << i << "." << std::endl;
		}
		if (msb(bb - 1) != 1ULL << i) {
			std::cout << "Test 2: wrong index at " << i << "." << std::endl;
		}
	}
}

void testIndexOf() {
	bb64 bb = 1ULL;
	int currIndex = 0;
	do {
		if (indexOf(bb) != currIndex) {
			std::cout << "indexOf returned " << indexOf(bb)
				<< ". It should have returned " << currIndex << ".\n";
		}
		if (popCount64(++bb) == 1) currIndex++;
	} while (bb != 1ULL << 15);

}

void testDirections()
{
	bool success = true;

	bb64 bb = 0x0000000000000100;
	if (northOne(bb) != 0x0000000000010000)
	{
		std::cerr << "ERROR TEST 1!" << std::endl;
		success = false;
	}

	if (southOne(bb) != 0x0000000000000001)
	{
		std::cerr << "ERROR TEST 2!" << std::endl;
		success = false;
	}

	if (westOne(bb) != 0x0000000000000000)
	{
		std::cerr << "ERROR TEST 3!" << std::endl;
		success = false;
	}

	if (eastOne(bb) != 0x0000000000000200)
	{
		std::cerr << "ERROR TEST 4!" << std::endl;
		success = false;
	}

	if (norEastOne(bb) != 0x0000000000020000)
	{
		std::cerr << "ERROR TEST 5!" << std::endl;
		success = false;
	}

	if (norWestOne(bb) != 0x0000000000000000)
	{
		std::cerr << "ERROR TEST 6!" << std::endl;
		success = false;
	}

	if (souEastOne(bb) != 0x0000000000000002)
	{
		std::cerr << "ERROR TEST 7!" << std::endl;
		success = false;
	}

	if (souWestOne(bb) != 0x0000000000000000)
	{
		std::cerr << "ERROR TEST 8!" << std::endl;
		success = false;
	}

	if (success) std::cout << "SUCCESS!" << std::endl;
}

void testBitBoards() {
	Position stdPosition = Position();

	std::cout << "wPawns" << std::endl;
	printBB(stdPosition.getPieceBB(wPawns));
	std::cout << std::endl;

	std::cout << "bPawns" << std::endl;
	printBB(stdPosition.getPieceBB(bPawns));
	std::cout << std::endl;

	std::cout << "wKnights" << std::endl;
	printBB(stdPosition.getPieceBB(wKnights));
	std::cout << std::endl;

	std::cout << "bKnights" << std::endl;
	printBB(stdPosition.getPieceBB(bKnights));
	std::cout << std::endl;

	std::cout << "wBishops" << std::endl;
	printBB(stdPosition.getPieceBB(wBishops));
	std::cout << std::endl;

	std::cout << "bBishops" << std::endl;
	printBB(stdPosition.getPieceBB(bBishops));
	std::cout << std::endl;

	std::cout << "wRooks" << std::endl;
	printBB(stdPosition.getPieceBB(wRooks));
	std::cout << std::endl;

	std::cout << "bRooks" << std::endl;
	printBB(stdPosition.getPieceBB(bRooks));
	std::cout << std::endl;

	std::cout << "wQueens" << std::endl;
	printBB(stdPosition.getPieceBB(wQueens));
	std::cout << std::endl;

	std::cout << "bQueens" << std::endl;
	printBB(stdPosition.getPieceBB(bQueens));
	std::cout << std::endl;

	std::cout << "wKing" << std::endl;
	printBB(stdPosition.getPieceBB(wKing));
	std::cout << std::endl;

	std::cout << "bKing" << std::endl;
	printBB(stdPosition.getPieceBB(bKing));
	std::cout << std::endl;

	std::cout << "wPieces" << std::endl;
	printBB(stdPosition.getPieceBB(wPieces));
	std::cout << std::endl;

	std::cout << "bPieces" << std::endl;
	printBB(stdPosition.getPieceBB(bPieces));
	std::cout << std::endl;

	std::cout << "occupied" << std::endl;
	printBB(stdPosition.getOccupiedBB());
	std::cout << std::endl;

	std::cout << "empty" << std::endl;
	printBB(stdPosition.getEmptyBB());
	std::cout << std::endl;
}

void testMakeMoves() {
	Position position = Position();
	Move move = Move(position, e2, e4, dblPawnPush);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());
	
	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());
	
	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEnPassantTarget());

	system("Pause");

	move = Move(position, e7, e5, dblPawnPush);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEnPassantTarget());

	system("Pause");

	move = Move(position, g1, f3, quietMove);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEnPassantTarget());

	system("Pause");

	move = Move(position, b8, c6, quietMove);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEnPassantTarget());

	system("Pause");

	move = Move(position, d2, d4, dblPawnPush);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEnPassantTarget());

	system("Pause");

	move = Move(position, e5, d4, capture);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEnPassantTarget());
}

void testUnmakeMoves() {
	Position pos;
	printChessBoard(pos);

	Move move = Move(pos, e2, e4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e7, e5, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, g1, f3, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, b8, c6, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, d2, d4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e5, d4, capture);
	pos.makeMove(move);
	printChessBoard(pos);

	for (int i = 0; i < 6; i++) {
		pos.unmakeMove();
		printChessBoard(pos);
	}
}

void testPromotions() {
	std::string cBoard;
	cBoard += "________";
	cBoard += "________";
	cBoard += "________";
	cBoard += "___k____";
	cBoard += "________";
	cBoard += "___K____";
	cBoard += "p_______";
	cBoard += "_R______";
	Position pos = Position(cBoard, BLACK);

	pos.makeMove(Move(pos, a2, b1, qPromoCapture));

	printChessBoard(pos);
}

void testBitManip() {
	bool success = true;
	bb64 b = 0;
	bbSetBit(b, 7);
	if (b != 128) success = false;
	bbSetBit(b, 5);
	if (b != 160) success = false;

	bbResetBit(b, 7);
	if (b != 32) success = false;
	bbResetBit(b, 5);
	if (b != 0) success = false;

	Position pos = Position();
	printBB(pos.getPieceBB(wPawns));

	if (success)
		std::cout << "SUCCESS" << std::endl;
	else
		std::cout << "FAILURE" << std::endl;
}

void testIcoMoveGenerator() {
	Position pos = Position();
	IcoMoveGenerator mGen = IcoMoveGenerator(pos);

	CandidateMoveList moveList = mGen.getMoveList();
	Move key[16] = { Move(pos, a2, a3, 0), Move(pos, b2, b3, 0), Move(pos, c2, c3, 0), Move(pos, d2, d3, 0), Move(pos, e2, e3, 0), Move(pos, f2, f3, 0), Move(pos, g2, g3, 0), Move(pos, h2, h3, 0),
						Move(pos, a2, a4, dblPawnPush), Move(pos, b2, b4, dblPawnPush), Move(pos, c2, c4, dblPawnPush), Move(pos, d2, d4, dblPawnPush), Move(pos, e2, e4, dblPawnPush), Move(pos, f2, f4, dblPawnPush), Move(pos, g2, g4, dblPawnPush), Move(pos, h2, h4, dblPawnPush) };

	//test white single pawn pushes on starting position
	for (int i = 0; i < 16; i++) {
		Move moveListMove = moveList.getMove(i);
		Move keyMove = key[i];
		if (!moveList.contains(keyMove)) {
			std::cerr << "MoveList index " << i << " is equal to:\n"
				<< "Move Piece: " << moveListMove.getMovPiece() << " instead of " << keyMove.getMovPiece() << std::endl
				<< "Capture Piece: " << moveListMove.getCaptPiece() << "instead of " << keyMove.getMovPiece() << std::endl
				<< "Move is " << bitString(moveListMove.getMove()) << "instead of " << bitString(keyMove.getMove()) << std::endl;
			return;
		}
	}

	pos.makeMove(Move(pos, e2, e4, 0));
	mGen = IcoMoveGenerator(pos);
	moveList = mGen.getMoveList();
	Move key2[16] = { Move(pos, a7, a6, 0), Move(pos, b7, b6, 0), Move(pos, c7, c6, 0), Move(pos, d7, d6, 0), Move(pos, e7, e6, 0), Move(pos, f7, f6, 0), Move(pos, g7, g6, 0), Move(pos, h7, h6, 0),
						Move(pos, a7, a5, dblPawnPush), Move(pos, b7, b5, dblPawnPush), Move(pos, c7, c5, dblPawnPush), Move(pos, d7, d5, dblPawnPush), Move(pos, e7, e5, dblPawnPush), Move(pos, f7, f5, dblPawnPush), Move(pos, g7, g5, dblPawnPush), Move(pos, h7, h5, dblPawnPush) };
	//test black single pawn pushes on position after 1. e4
	for (int i = 0; i < 16; i++) {
		Move moveListMove = moveList.getMove(i);
		Move keyMove = key2[i];
		if (!moveList.contains(keyMove)) {
			std::cerr << "MoveList index " << i << " is equal to:\n"
				<< "Move Piece: " << moveListMove.getMovPiece() << " instead of " << keyMove.getMovPiece() << std::endl
				<< "Capture Piece: " << moveListMove.getCaptPiece() << "instead of " << keyMove.getMovPiece() << std::endl
				<< "Move is " << bitString(moveListMove.getMove()) << "instead of " << bitString(keyMove.getMove()) << std::endl;
			return;
		}
	}

	std::cout << "SUCCESS" << std::endl;
}

void testMoves() {
	Position position = Position();
	Move move = Move(d2, e3, 0b0100);
	std::cout << "MOVE = " << move.getMove() << std::endl;
	printBits(move.getMove());
	std::cout << "FROM SQUARE = " << move.getFromSquare() << std::endl;
	printBits(move.getFromSquare());
	std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	printBits(move.getToSquare());
	std::cout << "FLAGS = " << move.getFlags() << std::endl;
	printBits(move.getFlags());
}

void testCandidateMoveList() {
	Position pos;
	Move ply[6];
	ply[0] = Move(pos, e2, e4, 0);
	ply[1] = Move(pos, e7, e5, 0);
	ply[2] = Move(pos, g1, f3, 0);
	ply[3] = Move(pos, b8, c6, 0);
	ply[4] = Move(pos, d2, d4, 0);
	ply[5] = Move(pos, e5, d4, capture);

	// Test Constructor
	CandidateMoveList list = CandidateMoveList(ply[0]);
	if (list.getSize() != 1) {
		std::cerr << "error on construction with size.\n";
		return;
	}

	// Test Add
	list.add(ply[1]);
	list.add(ply[2]);
	list.add(ply[3]);
	list.add(ply[4]);
	list.add(ply[5]);

	if (list.getSize() != 6) {
		std::cerr << "error on addition with size.\n";
		return;
	}
	for (int i = 0; i < 6; i++) {
		if (!list.getMove(i).isEqual(ply[i])) {
			std::cerr << "error on addition of ply " << i << ".\n";
			return;
		}
	}
	
	//Test Contains
	for(int i = 0; i < 6; i++) {
		if (!list.contains(ply[i])) {
			std::cerr << "error on test of contains of ply " << i << std::endl;
			return;
		}
	}

	//Test Remove
	list.remove(4);
	if (!list.getMove(4).isEqual(ply[5]) || list.getSize() != 5) {
		std::cerr << "error on removal of ply 4.\n";
		return;
	}

	list.remove(2);
	if (!(list.getMove(2).isEqual(ply[3]) && list.getMove(3).isEqual(ply[5])) || list.getSize() != 4) {
		std::cerr << "error of removal of ply 2.\n";
		return;
	}

	std::cout << "SUCCESS.\n";
}

void testPrintChess() {
	Position pos;
	printChessBoard(pos);

	Move move = Move(pos, e2, e4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e7, e5, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, g1, f3, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, b8, c6, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, d2, d4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e5, d4, capture);
	pos.makeMove(move);
	printChessBoard(pos);
}

void testEnPassant() {
	Position pos;
	printChessBoard(pos);

	Move move = Move(pos, e2, e4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, b7, b6, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e4, e5, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, d7, d5, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	//printBB(pos.getEnPassantTarget());

	move = Move(pos, e5, d6, enPassant);
	pos.makeMove(move);
	printChessBoard(pos);
}

void testPopCount() {
	bb64 bitset = 0x0000000000000001ULL;
	if (popCount64(bitset) != 1) {
		std::cerr << "ERROR popCount returns wrong value." << std::endl;
	}

	bitset = 0x0000000000000003ULL;
	if (popCount64(bitset) != 2) {
		std::cerr << "ERROR popCount returns wrong value." << std::endl;
	}

	bitset = 0xFFFFFFFFFFFFFFFFULL;
	if (popCount64(bitset) != 64) {
		std::cerr << "ERROR popCount returned " << popCount64(bitset)
			<< " instead of 64" << std::endl;
	}

	bitset = 0x000F00000000F00F;
	if (popCount64(bitset) != 12) {
		std::cerr << "ERROR popCount returns wrong value." << std::endl;
	}

	std::cout << "SUCCESS!" << std::endl;
}

void testBitScan() {
	bool success = true;
	bb64 bitboard = 0x0000000000000001;
	if (bitScanForward(bitboard) != 0 || bitScanReverse(bitboard) != 0) {
		std::cerr << "FAILURE TEST 1" << std::endl;
		success = false;
	}

	bitboard = 0x8000000000000001;
	if (bitScanForward(bitboard) != 0 || bitScanReverse(bitboard) != 63) {
		std::cerr << "FAILURE TEST 2" << std::endl;
		success = false;
	}

	bitboard = 0x000F000F00000000;
	if (bitScanForward(bitboard) != 32 || bitScanReverse(bitboard) != 51) {
		std::cerr << "FAILURE TEST 3" << std::endl;
		success = false;
	}

	if (success)
		std::cout << "SUCCESS!" << std::endl;
}

void testPositionRecord() {
	Position pos;
	bool success = true;

	Move move1 = Move(pos, e2, e4, dblPawnPush);
	pos.makeMove(move1);

	Move move2 = Move(pos, e7, e5, dblPawnPush);
	pos.makeMove(move2);

	Move move3 = Move(pos, g1, f3, quietMove);
	pos.makeMove(move3);

	Move move4 = Move(pos, b8, c6, quietMove);
	pos.makeMove(move4);

	Move move5 = Move(pos, d2, d4, dblPawnPush);
	pos.makeMove(move5);

	Move move6 = Move(pos, e5, d4, capture);
	pos.makeMove(move6);

	std::stack<positionRecord> stack = pos.getPositionRecord();
	positionRecord prev = stack.top();
	if (!prev.getPrevMove().isEqual(move6)
		|| prev.getEnPassantTarget() != 1ULL << d4
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 1." << std::endl;
		success = false;
	}
	stack.pop();

	prev = stack.top();
	if (!prev.getPrevMove().isEqual(move5)
		|| prev.getEnPassantTarget() != 0ULL
		|| prev.getFiftyMoveRule() != 2) {
		std::cerr << "Position Record FAILED test 2." << std::endl;
		success = false;
	}
	stack.pop();

	prev = stack.top();
	if (!prev.getPrevMove().isEqual(move4)
		|| prev.getEnPassantTarget() != 0ULL
		|| prev.getFiftyMoveRule() != 1) {
		std::cerr << "Position Record FAILED test 3." << std::endl;
		success = false;
	}
	stack.pop();

	prev = stack.top();
	if (!prev.getPrevMove().isEqual(move3)
		|| prev.getEnPassantTarget() != 1ULL << e5
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 4." << std::endl;
		success = false;
	}
	stack.pop();

	prev = stack.top();
	if (!prev.getPrevMove().isEqual(move2)
		|| prev.getEnPassantTarget() != 1ULL << e4
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 5." << std::endl;
		success = false;
	}
	stack.pop();

	prev = stack.top();
	if (!prev.getPrevMove().isEqual(move1)
		|| prev.getEnPassantTarget() != 0ULL
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 6." << std::endl;
		success = false;
	}
	stack.pop();

	if (success && stack.empty()) {
		std::cout << "SUCCESS!" << std::endl;
	}
}

int main() {

	/************************************************
	 *			BitManipulation Testing				*
	 ************************************************/
	/*
	std::string testBoard;
	cBoard += "rnbqkbnr";
	cBoard += "p__ppppp";
	cBoard += "________";
	cBoard += "________";
	cBoard += "__p_____";
	cBoard += "Pp______";
	cBoard += "_PPPPPPP";
	cBoard += "RNBQKBNR";
	*/

	/*
	Position* pos = &Position(testBoard, WHITE);
	bb64 pawnsToMove = pos->getPieceBB(wPawns);
	bb64 pawnPushTargets = (northOne(pawnsToMove) & pos->getEmptyBB()) | (northOne(northOne(pawnsToMove & RANKS[rank2]) & pos->getEmptyBB()) & pos->getEmptyBB());
	printBB(pawnPushTargets);
	*/

	//testPromotions();
	//testMsb();
	//testIndexOf();
	//testBitBoards();
	//testMakeMoves();
	//testUnmakeMoves();
	//testMoves();
	testIcoMoveGenerator();
	//testCandidateMoveList();
	//testBitManip();
	//testPrintChess();
	//testEnPassant();
	//testPopCount();
	//testBitScan();
	//testPositionRecord();
	//testDirections();

	system("Pause");
}
