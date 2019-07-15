class Position;
#include <iostream>
#include <stack>
#include "stdlib.h"
#include "Move.h"
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"

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
	position.setSideToMove(BLACK);
	Move move = Move(&position, e7, e5, dblPawnPush);
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

	Move move = Move(&pos, e2, e4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, e7, e5, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, g1, f3, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, b8, c6, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, d2, d4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, e5, d4, capture);
	pos.makeMove(move);
	printChessBoard(pos);

	for (int i = 0; i < 6; i++) {
		pos.unmakeMove();
		printChessBoard(pos);
	}
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

void testPrintChess() {
	Position pos;
	printChessBoard(pos);

	Move move = Move(&pos, e2, e4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, e7, e5, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, g1, f3, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, b8, c6, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, d2, d4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, e5, d4, capture);
	pos.makeMove(move);
	printChessBoard(pos);
}

void testEnPassant() {
	Position pos;
	printChessBoard(pos);

	Move move = Move(&pos, e2, e4, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, b7, b6, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, e4, e5, quietMove);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(&pos, d7, d5, dblPawnPush);
	pos.makeMove(move);
	printChessBoard(pos);

	//printBB(pos.getEnPassantTarget());

	move = Move(&pos, e5, d6, enPassant);
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

	Move move1 = Move(&pos, e2, e4, dblPawnPush);
	pos.makeMove(move1);

	Move move2 = Move(&pos, e7, e5, dblPawnPush);
	pos.makeMove(move2);

	Move move3 = Move(&pos, g1, f3, quietMove);
	pos.makeMove(move3);

	Move move4 = Move(&pos, b8, c6, quietMove);
	pos.makeMove(move4);

	Move move5 = Move(&pos, d2, d4, dblPawnPush);
	pos.makeMove(move5);

	Move move6 = Move(&pos, e5, d4, capture);
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
	//testBitBoards();
	//testMakeMoves();
	//testUnmakeMoves();
	//testMoves();
	//testBitManip();
	testPrintChess();
	//testEnPassant();
	//testPopCount();
	//testBitScan();
	//testPositionRecord();
	//testDirections();

	system("Pause");
}