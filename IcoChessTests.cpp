class Position;
#include <iostream>
#include <stack>
#include <string>
#include "stdlib.h"

#include "Move.h"
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"
#include "IcoChessEngine.h"

namespace IcoChess
{

void testConstants()
{
	std::cout << "Ico Chess constants." << std::endl;
	std::cout << "Ranks printed 1 - 8" << std::endl;
	for (int i = 0; i < 8; i++) {
		printBB(RANK[i]);
	}

	std::cout << std::endl;
	std::cout << "Files printed A - H" << std::endl;
	for (int i = 0; i < 8; i++) {
		printBB(FILE[i]);
	}

	std::cout << std::endl;
	std::cout << "Print left diagonals, then right diagonals." << std::endl;
	for (int i = 0; i < 16; i++) {
		printBB(DIAGONAL[i]);
	}

	std::cout << std::endl;
	std::cout << "Print left diagonals, then right diagonals." << std::endl;
	for (int i = 0; i < 16; i++) {
		printBB(ANTI_DIAGONAL[i]);
	}
}

void testMsb()
{
	bb64 bb = 0;
	if (msb(bb) != (unsigned long long) - 1) std::cout << "Test 1: wrong index at 0." << std::endl;
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

void testIndexOf()
{
	bb64 bb = 1ULL;
	int currIndex = 0;
	do {
		if (indexOf(bb) != currIndex) {
			std::cout << "indexOf returned " << indexOf(bb)
				<< ". It should have returned " << currIndex << ".\n";
		}
		if (popCount64(++bb) == 1) currIndex++;
	} while (bb != 1ULL << 29);

}

void testDirections()
{
	bool success = true;

	bb64 bb = 0x0000000000000100;
	if (northOne(bb) != 0x0000000000010000) {
		std::cerr << "ERROR TEST 1!" << std::endl;
		success = false;
	}

	if (southOne(bb) != 0x0000000000000001) {
		std::cerr << "ERROR TEST 2!" << std::endl;
		success = false;
	}

	if (westOne(bb) != 0x0000000000000000) {
		std::cerr << "ERROR TEST 3!" << std::endl;
		success = false;
	}

	if (eastOne(bb) != 0x0000000000000200) {
		std::cerr << "ERROR TEST 4!" << std::endl;
		success = false;
	}

	if (norEastOne(bb) != 0x0000000000020000) {
		std::cerr << "ERROR TEST 5!" << std::endl;
		success = false;
	}

	if (norWestOne(bb) != 0x0000000000000000) {
		std::cerr << "ERROR TEST 6!" << std::endl;
		success = false;
	}

	if (souEastOne(bb) != 0x0000000000000002) {
		std::cerr << "ERROR TEST 7!" << std::endl;
		success = false;
	}

	if (souWestOne(bb) != 0x0000000000000000) {
		std::cerr << "ERROR TEST 8!" << std::endl;
		success = false;
	}

	if (success) std::cout << "SUCCESS!" << std::endl;
}

void testBitBoards()
{
	Position stdPosition = Position();

	std::cout << "W_PAWN" << std::endl;
	printBB(stdPosition.getPieceBB(W_PAWN));
	std::cout << std::endl;

	std::cout << "B_PAWN" << std::endl;
	printBB(stdPosition.getPieceBB(B_PAWN));
	std::cout << std::endl;

	std::cout << "W_KNIGHT" << std::endl;
	printBB(stdPosition.getPieceBB(W_KNIGHT));
	std::cout << std::endl;

	std::cout << "B_KNIGHT" << std::endl;
	printBB(stdPosition.getPieceBB(B_KNIGHT));
	std::cout << std::endl;

	std::cout << "W_BISHOP" << std::endl;
	printBB(stdPosition.getPieceBB(W_BISHOP));
	std::cout << std::endl;

	std::cout << "B_BISHOP" << std::endl;
	printBB(stdPosition.getPieceBB(B_BISHOP));
	std::cout << std::endl;

	std::cout << "W_ROOK" << std::endl;
	printBB(stdPosition.getPieceBB(W_ROOK));
	std::cout << std::endl;

	std::cout << "B_ROOK" << std::endl;
	printBB(stdPosition.getPieceBB(B_ROOK));
	std::cout << std::endl;

	std::cout << "W_QUEEN" << std::endl;
	printBB(stdPosition.getPieceBB(W_QUEEN));
	std::cout << std::endl;

	std::cout << "B_QUEEN" << std::endl;
	printBB(stdPosition.getPieceBB(B_QUEEN));
	std::cout << std::endl;

	std::cout << "W_KING" << std::endl;
	printBB(stdPosition.getPieceBB(W_KING));
	std::cout << std::endl;

	std::cout << "B_KING" << std::endl;
	printBB(stdPosition.getPieceBB(B_KING));
	std::cout << std::endl;

	std::cout << "W_PIECE" << std::endl;
	printBB(stdPosition.getPieceBB(W_PIECE));
	std::cout << std::endl;

	std::cout << "B_PIECE" << std::endl;
	printBB(stdPosition.getPieceBB(B_PIECE));
	std::cout << std::endl;

	std::cout << "occupied" << std::endl;
	printBB(stdPosition.getOccupiedBB());
	std::cout << std::endl;

	std::cout << "empty" << std::endl;
	printBB(stdPosition.getEmptyBB());
	std::cout << std::endl;
}

void testMakeMoves()
{
	Position position = Position();
	Move move = Move(position, e2, e4, DOUBLE_PAWN_PUSH);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEN_PASSANTTarget());

	system("Pause");

	move = Move(position, e7, e5, DOUBLE_PAWN_PUSH);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEN_PASSANTTarget());

	system("Pause");

	move = Move(position, g1, f3, QUIET_MOVE);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEN_PASSANTTarget());

	system("Pause");

	move = Move(position, b8, c6, QUIET_MOVE);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEN_PASSANTTarget());

	system("Pause");

	move = Move(position, d2, d4, DOUBLE_PAWN_PUSH);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEN_PASSANTTarget());

	system("Pause");

	move = Move(position, e5, d4, CAPTURE);
	//std::cout << "TO SQUARE = " << move.getToSquare() << std::endl;
	std::cout << "Before move" << std::endl;
	printBB(position.getOccupiedBB());

	position.makeMove(move);
	std::cout << std::endl << "After move" << std::endl;
	printBB(position.getOccupiedBB());

	std::cout << std::endl << "En Passant Target" << std::endl;
	printBB(position.getEN_PASSANTTarget());
}

void testUnmakeMoves()
{
	Position pos;
	printChessBoard(pos);

	Move move = Move(pos, e2, e4, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e7, e5, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, g1, f3, QUIET_MOVE);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, b8, c6, QUIET_MOVE);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, d2, d4, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e5, d4, CAPTURE);
	pos.makeMove(move);
	printChessBoard(pos);

	for (int i = 0; i < 6; i++) {
		pos.unmakeMove();
		printChessBoard(pos);
	}
}

void testPromotions()
{
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

	pos.makeMove(Move(pos, a2, b1, PROMOTE_TO_QUEENCAPTURE));

	printChessBoard(pos);
}

void testBitManip()
{
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
	printBB(pos.getPieceBB(W_PAWN));

	if (success)
		std::cout << "SUCCESS" << std::endl;
	else
		std::cout << "FAILURE" << std::endl;
}

/*void testIcoMoveGenerator() {
	Position pos = Position();
	//Position *pos = &Position();
	IcoMoveGenerator mGen = IcoMoveGenerator(&pos);

	CandidateMoveList moveList = mGen.getMoveList();
	Move key[16] = { Move(pos, a2, a3, 0), Move(pos, b2, b3, 0), Move(pos, c2, c3, 0), Move(pos, d2, d3, 0), Move(pos, e2, e3, 0), Move(pos, f2, f3, 0), Move(pos, g2, g3, 0), Move(pos, h2, h3, 0),
					Move(pos, a2, a4, 1), Move(pos, b2, b4, 1), Move(pos, c2, c4, 1), Move(pos, d2, d4, 1), Move(pos, e2, e4, 1), Move(pos, f2, f4, 1), Move(pos, g2, g4, 1), Move(pos, h2, h4, 1) };

	//test white single pawn pushes on starting position
	for (int i = 0; i < 16; i++) {
		if (!moveList.contains(key[i])) {
			std::cerr << "Move generator did not generate an expected move: ";
			printMove(key[i]);
			std::cerr << std::endl;
		}
	}

	pos.makeMove(Move(pos, e2, e4, 0));
	mGen = IcoMoveGenerator(&pos);
	moveList = mGen.getMoveList();
	Move key2[16] = { Move(pos, a7, a6, 0), Move(pos, b7, b6, 0), Move(pos, c7, c6, 0), Move(pos, d7, d6, 0), Move(pos, e7, e6, 0), Move(pos, f7, f6, 0), Move(pos, g7, g6, 0), Move(pos, h7, h6, 0),
					 Move(pos, a7, a5, 1), Move(pos, b7, b5, 1), Move(pos, c7, c5, 1), Move(pos, d7, d5, 1), Move(pos, e7, e5, 1), Move(pos, f7, f5, 1), Move(pos, g7, g5, 1), Move(pos, h7, h5, 1) };
	//test black single pawn pushes on position after 1. e4
	for (int i = 0; i < 16; i++) {
		if (!moveList.contains(key2[i])) {
			std::cerr << "Move generator did not generate an expected move: " << key2[i].toString() << std::endl;
		}
	}

	std::cout << "SUCCESS" << std::endl;
}*/

void testMoves()
{
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

void testCandidateMoveList()
{
	Move ply[6];
	ply[0] = Move(e2, e4, 0);
	ply[1] = Move(e7, e5, 0);
	ply[2] = Move(g1, f3, 0);
	ply[3] = Move(b8, c6, 0);
	ply[4] = Move(d2, d4, 0);
	ply[5] = Move(e5, d4, CAPTURE);

	CandidateMoveList list = CandidateMoveList(ply[0]);
	if (list.getSize() != 1) {
		std::cerr << "error on construction with size.\n";
		return;
	}

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

void testPrintChess()
{
	Position pos;
	printChessBoard(pos);

	Move move = Move(pos, e2, e4, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e7, e5, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, g1, f3, QUIET_MOVE);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, b8, c6, QUIET_MOVE);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, d2, d4, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e5, d4, CAPTURE);
	pos.makeMove(move);
	printChessBoard(pos);
}

void testEN_PASSANT()
{
	Position pos;
	printChessBoard(pos);

	Move move = Move(pos, e2, e4, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, b7, b6, QUIET_MOVE);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, e4, e5, QUIET_MOVE);
	pos.makeMove(move);
	printChessBoard(pos);

	move = Move(pos, d7, d5, DOUBLE_PAWN_PUSH);
	pos.makeMove(move);
	printChessBoard(pos);

	//printBB(pos.getEN_PASSANTTarget());

	move = Move(pos, e5, d6, EN_PASSANT);
	pos.makeMove(move);
	printChessBoard(pos);
}

void testPopCount()
{
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

void testBitScan()
{
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

void testPositionRecord()
{
	Position pos;
	bool success = true;

	Move move1 = Move(pos, e2, e4, DOUBLE_PAWN_PUSH);
	pos.makeMove(move1);

	Move move2 = Move(pos, e7, e5, DOUBLE_PAWN_PUSH);
	pos.makeMove(move2);

	Move move3 = Move(pos, g1, f3, QUIET_MOVE);
	pos.makeMove(move3);

	Move move4 = Move(pos, b8, c6, QUIET_MOVE);
	pos.makeMove(move4);

	Move move5 = Move(pos, d2, d4, DOUBLE_PAWN_PUSH);
	pos.makeMove(move5);

	Move move6 = Move(pos, e5, d4, CAPTURE);
	pos.makeMove(move6);

	std::vector<positionRecord> stack = pos.getPositionRecord();
	positionRecord prev = stack.back();
	if (!prev.getPrevMove().isEqual(move6)
		|| prev.getEN_PASSANTTarget() != 1ULL << d4
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 1." << std::endl;
		success = false;
	}
	stack.pop_back();

	prev = stack.back();
	if (!prev.getPrevMove().isEqual(move5)
		|| prev.getEN_PASSANTTarget() != 0ULL
		|| prev.getFiftyMoveRule() != 2) {
		std::cerr << "Position Record FAILED test 2." << std::endl;
		success = false;
	}
	stack.pop_back();

	prev = stack.back();
	if (!prev.getPrevMove().isEqual(move4)
		|| prev.getEN_PASSANTTarget() != 0ULL
		|| prev.getFiftyMoveRule() != 1) {
		std::cerr << "Position Record FAILED test 3." << std::endl;
		success = false;
	}
	stack.pop_back();

	prev = stack.back();
	if (!prev.getPrevMove().isEqual(move3)
		|| prev.getEN_PASSANTTarget() != 1ULL << e5
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 4." << std::endl;
		success = false;
	}
	stack.pop_back();

	prev = stack.back();
	if (!prev.getPrevMove().isEqual(move2)
		|| prev.getEN_PASSANTTarget() != 1ULL << e4
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 5." << std::endl;
		success = false;
	}
	stack.pop_back();

	prev = stack.back();
	if (!prev.getPrevMove().isEqual(move1)
		|| prev.getEN_PASSANTTarget() != 0ULL
		|| prev.getFiftyMoveRule() != 0) {
		std::cerr << "Position Record FAILED test 6." << std::endl;
		success = false;
	}
	stack.pop_back();

	if (success && stack.empty()) {
		std::cout << "SUCCESS!" << std::endl;
	}
}

void testSlidingAttacks()
{
	for (int i = 0; i < 7; i++) {
		for (int sq = a1; sq <= h8; sq++) {
			printBB(ATTACK_RAYS[sq][i]);
			std::cout << std::endl;
		}
	}
}

void testEngine()
{
	IcoChessEngine ico;
	ico.generateMoves();

	CandidateMoveList moves = ico.getMoves();

	for (int i = 0; i < moves.getSize(); i++) {
		Position pos;
		pos.makeMove(moves.getMove(i));
		printChessBoard(pos);
	}
}

void testPawnMovesBlackEnPassant()
{
	std::cout << "Test pawn moves: black en passant:" << std::endl;
	std::cout << "===============================================" << std::endl;
	std::cout << " Moves after:	1.e4 e5  2. d4 exd4  3. c4 ..." << std::endl;
	Position pos;
	pos.makeMove(Move(pos, e2, e4, DOUBLE_PAWN_PUSH));
	pos.makeMove(Move(pos, e7, e5, DOUBLE_PAWN_PUSH));
	pos.makeMove(Move(pos, d2, d4, DOUBLE_PAWN_PUSH));
	pos.makeMove(Move(pos, e5, d4, CAPTURE));
	pos.makeMove(Move(pos, c2, c4, DOUBLE_PAWN_PUSH));

	IcoChessEngine ico(pos);
	ico.generateMoves();

	CandidateMoveList moves = ico.getMoves();
	std::cout << "    " << moves.getSize() << " moves found." << std::endl;
	std::cout << "===============================================" << std::endl;

	for (int i = 0; i < moves.getSize(); i++) {
		std::cout << moves.getMove(i).toString() << std::endl;
		Position p = ico.getPosition();
		p.makeMove(moves.getMove(i));
		printChessBoard(p);
	}
}

void testPawnMovesWhiteEnPassant()
{
	std::cout << "Test pawn moves: white en passant:" << std::endl;
	std::cout << "===============================================" << std::endl;
	std::cout << " Moves after:	1.e4 d5  2. exd5 c5  " << std::endl;
	Position pos;
	pos.makeMove(Move(pos, e2, e4, DOUBLE_PAWN_PUSH));
	pos.makeMove(Move(pos, d7, d5, DOUBLE_PAWN_PUSH));
	pos.makeMove(Move(pos, e4, d5, CAPTURE));
	pos.makeMove(Move(pos, c7, c5, DOUBLE_PAWN_PUSH));

	IcoChessEngine ico(pos);
	ico.generateMoves();

	CandidateMoveList moves = ico.getMoves();

	std::cout << "    " << moves.getSize() << " moves found." << std::endl;
	std::cout << "===============================================" << std::endl;

	for (int i = 0; i < moves.getSize(); i++) {
		std::cout << moves.getMove(i).toString() << std::endl;
		Position p = ico.getPosition();
		p.makeMove(moves.getMove(i));
		printChessBoard(p);
	}
}

void testPawnMovesWhiteEnPassantFromA5()
{
	std::cout << "Test 3, white en passant from a5:" << std::endl;
	std::cout << "===============================================" << std::endl;
	std::cout << " Moves after:	1.a2 d5  2. a5 b5  " << std::endl;
	Position pos;
	pos.makeMove(Move(pos, a2, a4, DOUBLE_PAWN_PUSH));
	pos.makeMove(Move(pos, d7, d5, DOUBLE_PAWN_PUSH));
	pos.makeMove(Move(pos, a4, a5, QUIET_MOVE));
	pos.makeMove(Move(pos, c7, c5, DOUBLE_PAWN_PUSH));

	IcoChessEngine ico(pos);
	ico.generateMoves();

	CandidateMoveList moves = ico.getMoves();

	std::cout << "    " << moves.getSize() << " moves found." << std::endl;
	std::cout << "===============================================" << std::endl;
	for (int i = 0; i < moves.getSize(); i++) {
		std::cout << moves.getMove(i).toString() << std::endl;
		Position p = ico.getPosition();
		p.makeMove(moves.getMove(i));
		printChessBoard(p);
	}
}

void testMoveGeneration()
{
	std::cout << "    BEGIN MOVE GENERATION TESTS." << std::endl;
	testPawnMovesBlackEnPassant();
	testPawnMovesWhiteEnPassant();
	testPawnMovesWhiteEnPassantFromA5();
}

void testLineAttacks()
{
	std::cout << "Test line attacks:" << std::endl;
	std::cout << "===============================================" << std::endl;

	std::string testBoard;
	testBoard += "________";
	testBoard += "_____P__";
	testBoard += "________";
	testBoard += "________";
	testBoard += "_p___R_p";
	testBoard += "________";
	testBoard += "________";
	testBoard += "________";

	Position pos(testBoard, WHITE);
	printChessBoard(pos);

	std::cout << "the white rooks line attack bitboard" << std::endl;
	IcoChessEngine ico(pos);
	printBB(ico.lineAttacks(f4));
	std::cout << "===============================================" << std::endl;
}

void testDiagonalAttacks()
{
	std::cout << "Test line attacks:" << std::endl;
	std::cout << "===============================================" << std::endl;

	std::string testBoard;
	testBoard += "________";
	testBoard += "_____P__";
	testBoard += "________";
	testBoard += "______p_";
	testBoard += "_p___B_p";
	testBoard += "________";
	testBoard += "________";
	testBoard += "__K_____";

	Position pos(testBoard, WHITE);
	printChessBoard(pos);

	std::cout << "the white bishop's diagonal attack bitboard" << std::endl;
	IcoChessEngine ico(pos);
	printBB(ico.diagonalAttacks(f4));
	std::cout << "===============================================" << std::endl;
}

} // End namespace IcoChess

int main()
{
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

	//IcoChess::testConstants();
	//testPromotions();
	//testMsb();
	//testIndexOf();
	//testBitBoards();
	//testMakeMoves();
	//testUnmakeMoves();
	//testMoves();
	//testIcoMoveGenerator();
	//testCandidateMoveList();
	//testBitManip();
	//testPrintChess();
	//testEN_PASSANT();
	//testPopCount();
	//testBitScan();
	//testPositionRecord();
	//testDirections();
	//IcoChess::testSlidingAttacks();
	//testEngine();
	//IcoChess::testMoveGeneration();
	//IcoChess::testLineAttacks();
	IcoChess::testDiagonalAttacks();



	system("Pause");
}