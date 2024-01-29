#ifndef POSITION_H
#define POSITION_H

#include <string>

#include "BoardRepresentation.hpp"

namespace IcoChess {

class Position {
public:
    Position();
    Position(std::string fen);

    bb64 pieceBitboard(PieceType pt);
    Side sideToMove();
    bool castleRights(Side side, CastleFlag castle_side);
    bb64 enPassantTarget();
    int ply();

private:
    Side side_to_move = WHITE;
    char castle_rights = 0xF;
    int ply_ = 0;
    bb64 en_passant_target = 0ULL;
    bb64 piece_bitboards[NUM_PIECE_TYPES] = {};

    void placePiece(PieceType piece, int rank, int file);
};

} // namespace IcoChess
#endif