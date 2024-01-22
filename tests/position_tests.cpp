#include <gtest/gtest.h>

#include <string>

#include "../src/Position.hpp"

namespace IcoChessTest {

using namespace IcoChess;

const bb64 STARTING_POSITION[14] =
{
    RANK_2,
    B_FILE | G_FILE & RANK_1,
    C_FILE | F_FILE & RANK_1,
    A_FILE | H_FILE & RANK_1,
    D_FILE & RANK_1,
    E_FILE & RANK_1,
    RANK_1 | RANK_2,
    RANK_7,
    B_FILE | G_FILE & RANK_8,
    C_FILE | F_FILE & RANK_8,
    A_FILE | H_FILE & RANK_8,
    D_FILE & RANK_8,
    E_FILE & RANK_8,
    RANK_7 | RANK_8
};

TEST(unit_tests_position, test_file_and_rank_constants_are_little_endian) {
    ASSERT_EQ(A_FILE, 0x0101010101010101);
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

TEST(unit_tests_position, standard_position_can_be_created) {
    Position pos;

    ASSERT_EQ(pos.sideToMove(), WHITE);
    ASSERT_TRUE(pos.castleRights(WHITE, KINGSIDE));
    ASSERT_TRUE(pos.castleRights(WHITE, QUEENSIDE));
    ASSERT_TRUE(pos.castleRights(BLACK, KINGSIDE));
    ASSERT_TRUE(pos.castleRights(BLACK, QUEENSIDE));
    ASSERT_EQ(pos.enPassantTarget(), 0);
    ASSERT_EQ(pos.ply(), 0);

    for (int pt = W_PAWN; pt <= B_KING; pt++) {
        ASSERT_EQ(pos.pieceBitboard(static_cast<PieceType>(pt)), STARTING_POSITION[pt]);
    }
}

/*
TEST(unit_tests_position, test_can_read_from_fen_string) {
    std::string startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Position pos{startpos};
    ASSERT_EQ
}
*/
} // namespace IcoChessTest