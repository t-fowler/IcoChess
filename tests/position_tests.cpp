#include <gtest/gtest.h>

#include <string>

#include "../src/Position.hpp"

namespace IcoChessTest {

using namespace IcoChess;

struct StartingPosition
{
    const bb64
    W_PAWN = 0x00'00'00'00'00'00'FF'00,
    W_KNIGHT = 0x00'00'00'00'00'00'00'42,
    W_BISHOP = 0x00'00'00'00'00'00'00'24,
    W_ROOK = 0x00'00'00'00'00'00'00'81,
    W_QUEEN = 0x00'00'00'00'00'00'00'08,
    W_KING = 0x00'00'00'00'00'00'00'10,
    W_PIECE = 0x00'00'00'00'00'00'FF'FF,
    B_PAWN = 0x00'FF'00'00'00'00'00'00,
    B_KNIGHT = 0x42'00'00'00'00'00'00'00,
    B_BISHOP = 0x24'00'00'00'00'00'00'00,
    B_ROOK = 0x81'00'00'00'00'00'00'00,
    B_QUEEN = 0x08'00'00'00'00'00'00'00,
    B_KING = 0x10'00'00'00'00'00'00'00,
    B_PIECE = 0xFF'FF'00'00'00'00'00'00,
    NO_PIECE = 0x00'00'FF'FF'FF'FF'00'00;
} startingPosition;

bool positionMatchesFenString(std::string fen, const Position& pos) {
    /*bb64 []
    for (int rank = 7; i > 0; i--) {
        // find the '/' demarcing the end of the row

    }
    */
    return false;
}

/** This test confirms that the board constants are correctly set. They should be
ordered in rank-file little endian mapping.*/
TEST(unit_tests_position, test_file_and_rank_constants_are_little_endian) {
    ASSERT_EQ(A_FILE, 0x01'01'01'01'01'01'01'01);
    ASSERT_EQ(B_FILE, 0x0202020202020202);
    ASSERT_EQ(C_FILE, 0x0404040404040404);
    ASSERT_EQ(D_FILE, 0x0808080808080808);
    ASSERT_EQ(E_FILE, 0x1010101010101010);
    ASSERT_EQ(F_FILE, 0x2020202020202020);
    ASSERT_EQ(G_FILE, 0x4040404040404040);
    ASSERT_EQ(H_FILE, 0x8080808080808080);

    ASSERT_EQ(RANK_1, 0x00000000000000FF);
    ASSERT_EQ(RANK_2, 0x000000000000FF00);
    ASSERT_EQ(RANK_3, 0x0000000000FF0000);
    ASSERT_EQ(RANK_4, 0x00000000FF000000);
    ASSERT_EQ(RANK_5, 0x000000FF00000000);
    ASSERT_EQ(RANK_6, 0x0000FF0000000000);
    ASSERT_EQ(RANK_7, 0x00FF000000000000);
    ASSERT_EQ(RANK_8, 0xFF00000000000000);
}

TEST(unit_tests_position, test_standard_position_can_be_created) {
    Position pos;

    ASSERT_EQ(pos.sideToMove(), WHITE);
    ASSERT_TRUE(pos.castleRights(WHITE, KINGSIDE));
    ASSERT_TRUE(pos.castleRights(WHITE, QUEENSIDE));
    ASSERT_TRUE(pos.castleRights(BLACK, KINGSIDE));
    ASSERT_TRUE(pos.castleRights(BLACK, QUEENSIDE));
    ASSERT_EQ(pos.enPassantTarget(), 0);
    ASSERT_EQ(pos.ply(), 0);
    ASSERT_EQ(pos.pieceBitboard(W_PAWN), startingPosition.W_PAWN);
    ASSERT_EQ(pos.pieceBitboard(W_KNIGHT), startingPosition.W_KNIGHT);
    ASSERT_EQ(pos.pieceBitboard(W_BISHOP), startingPosition.W_BISHOP);
    ASSERT_EQ(pos.pieceBitboard(W_ROOK), startingPosition.W_ROOK);
    ASSERT_EQ(pos.pieceBitboard(W_QUEEN), startingPosition.W_QUEEN);
    ASSERT_EQ(pos.pieceBitboard(W_KING), startingPosition.W_KING);
    ASSERT_EQ(pos.pieceBitboard(W_PIECE), startingPosition.W_PIECE);
    ASSERT_EQ(pos.pieceBitboard(B_PAWN), startingPosition.B_PAWN);
    ASSERT_EQ(pos.pieceBitboard(B_KNIGHT), startingPosition.B_KNIGHT);
    ASSERT_EQ(pos.pieceBitboard(B_BISHOP), startingPosition.B_BISHOP);
    ASSERT_EQ(pos.pieceBitboard(B_ROOK), startingPosition.B_ROOK);
    ASSERT_EQ(pos.pieceBitboard(B_QUEEN), startingPosition.B_QUEEN);
    ASSERT_EQ(pos.pieceBitboard(B_KING), startingPosition.B_KING);
    ASSERT_EQ(pos.pieceBitboard(B_PIECE), startingPosition.B_PIECE);
    ASSERT_EQ(pos.pieceBitboard(NO_PIECE), startingPosition.NO_PIECE);
}


TEST(unit_tests_position, test_can_read_from_fen_string) {
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Position startpos(fen);
    ASSERT_TRUE(positionMatchesFenString(fen, startpos)) << "1: Starting position fen failed.";

    fen = "8/5p1p/2R5/1P1K1kp1/6P1/8/P2p1P1P/8 b - g3 0 36" ;
    Position kasparov_timman(fen);
    ASSERT_TRUE(positionMatchesFenString(fen, kasparov_timman)) << "2: Kasparov - Timman fen failed.";
}

} // namespace IcoChessTest