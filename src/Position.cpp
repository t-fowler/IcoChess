#include "Position.hpp"

namespace IcoChess {

Position::Position() {
    side_to_move = WHITE;
    castle_rights = 0b1111;
    en_passant_target = 0ULL;
    ply_ = 0;

}

bb64 Position::pieceBitboard(PieceType pt) {
    return 0ULL;
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