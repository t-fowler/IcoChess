#include "Position.hpp"

namespace IcoChess {

Position::Position() {
    side_to_move = WHITE;
    castle_rights = 0b1111;
    en_passant_target = 0ULL;
    ply_ = 0;
    piece_bitboards[W_PAWN] = RANK_2;
    piece_bitboards[B_PAWN] = RANK_7;
    piece_bitboards[W_KNIGHT] = B_FILE | G_FILE & RANK_1;
    piece_bitboards[B_KNIGHT] = B_FILE | G_FILE & RANK_8;
    piece_bitboards[W_BISHOP] = C_FILE | F_FILE & RANK_1;
    piece_bitboards[B_BISHOP] = C_FILE | F_FILE & RANK_8;
    piece_bitboards[W_ROOK] = A_FILE | H_FILE & RANK_1;
    piece_bitboards[B_ROOK] = A_FILE | H_FILE & RANK_8;
    piece_bitboards[W_QUEEN] = D_FILE & RANK_1;
    piece_bitboards[B_QUEEN] = D_FILE & RANK_8;
    piece_bitboards[W_KING] = E_FILE & RANK_1;
    piece_bitboards[B_KING] = E_FILE & RANK_8;
    piece_bitboards[W_PIECE] = RANK_1 | RANK_2;
    piece_bitboards[B_PIECE] = RANK_8 | RANK_7;
    piece_bitboards[NO_PIECE] = !(piece_bitboards[W_PIECE] | piece_bitboards[B_PIECE]);
}

bb64 Position::pieceBitboard(PieceType pt) {
    return piece_bitboards[pt];
}

Side Position::sideToMove() {
    return side_to_move;
}

bool Position::castleRights(Side side, CastleFlag castle_side) {
    if (side == BLACK) {
        return castle_rights >> 2 & castle_side;
    }
    return castle_rights & castle_side;
}

bb64 Position::enPassantTarget() {
    return en_passant_target;
}

int Position::ply() {
    return ply_;
}

} // namespace Icochess