#ifndef POSITION_H
#define POSITION_H

#include "BoardRepresentation.hpp"

namespace IcoChess {

class Position {
public:
    Position();

    bb64 pieceBitboard(PieceType pt);
    Side sideToMove();
    bool castleRights(Side side, CastleFlag castle_side);
    bb64 enPassantTarget();
    int ply();

private:
    Side side_to_move;
    char castle_rights;
    int ply_;
    bb64 en_passant_target;
    bb64 piece_bitboards[NUM_PIECE_TYPES];
};

} // namespace IcoChess
#endif