#include "Position.hpp"

namespace IcoChess {

void Position::placePiece(PieceType piece, int rank, int file) {
    // TO-DO: Make sure the square is empty.
    piece_bitboards[piece] |= 1ULL << (8 * rank + file);
}

Position::Position() {
    side_to_move = WHITE;
    castle_rights = 0b1111;
    en_passant_target = 0ULL;
    ply_ = 0;
    piece_bitboards[W_PAWN] = RANK_2;
    piece_bitboards[B_PAWN] = RANK_7;
    piece_bitboards[W_KNIGHT] = (B_FILE | G_FILE) & RANK_1;
    piece_bitboards[B_KNIGHT] = (B_FILE | G_FILE) & RANK_8;
    piece_bitboards[W_BISHOP] = (C_FILE | F_FILE) & RANK_1;
    piece_bitboards[B_BISHOP] = (C_FILE | F_FILE) & RANK_8;
    piece_bitboards[W_ROOK] = (A_FILE | H_FILE) & RANK_1;
    piece_bitboards[B_ROOK] = (A_FILE | H_FILE) & RANK_8;
    piece_bitboards[W_QUEEN] = D_FILE & RANK_1;
    piece_bitboards[B_QUEEN] = D_FILE & RANK_8;
    piece_bitboards[W_KING] = E_FILE & RANK_1;
    piece_bitboards[B_KING] = E_FILE & RANK_8;
    piece_bitboards[W_PIECE] = RANK_1 | RANK_2;
    piece_bitboards[B_PIECE] = RANK_8 | RANK_7;
    piece_bitboards[NO_PIECE] = ~(piece_bitboards[W_PIECE] | piece_bitboards[B_PIECE]);
}

Position::Position(std::string fen) {

    // Piece Placement
    size_t delim = std::string::npos;
    for (int rank = 8; rank >= 1; rank--) {
        delim = fen.find("/");
        if (delim == std::string::npos) {
            delim = fen.find(" ");
        }
        int file = 0;
        std::string rankString = fen.substr(0, delim);
        fen.erase(0, delim + 1);

        for (auto ch : rankString) {
            switch (ch) {    
            case 'P': placePiece(W_PAWN, rank, file);
            case 'N': placePiece(W_KNIGHT, rank, file);
            case 'B': placePiece(W_BISHOP, rank, file);
            case 'R': placePiece(W_ROOK, rank, file);
            case 'Q': placePiece(W_QUEEN, rank, file);
            case 'K': placePiece(W_KING, rank, file);
            case 'p': placePiece(B_PAWN, rank, file);
            case 'n': placePiece(B_KNIGHT, rank, file);
            case 'b': placePiece(B_BISHOP, rank, file);
            case 'r': placePiece(B_ROOK, rank, file);
            case 'q': placePiece(B_QUEEN, rank, file);
            case 'k': placePiece(B_KING, rank, file);
            case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8':
                file += ch - '1';
            default:
                ; // invalid character in FEN. Throw error?
            }
        file++;
        }
    }

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