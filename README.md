# IcoChess Design Document

## Overview

IcoChess is my first attempt at writing a chess engine. 

## Design

### Components

The components for a chess engine are well documented.

1. **Board representation**: A model to store the state of the game. The state (position)
  is defined by more than the board configuration. It consists of:
  * The arrangment of pieces on the board
  * The current side to move
  * The available castling rights for each player
  * The possibility of an en passant capture
  * the halfmove clock
1. **Move generator**: Determines all the legal (or pseudolegal) moves possible in the position.
2. **Evaluation**: An function for determining the value of a position. Which side is winning?
3. **Search**: Examines which moves to look at based on the evaluation of the position.
  Searches through the game tree for the best outcome for a particular side.
                                                                                              
### Board Representation

Going with a bitboard approach, the board representation will be piece centric.
Each piece type will have a 64 bit unsigned integer to represent the location of
those pieces on the chessboard. Here are the current set of tracked bitboards.

* **Piece bitboards**: One bitboard for each set of white or black rooks, knights, bishops,
  Queens, Kings, pawns.
* **Occupied**: The set of occupied squares.
* **En passant target**: A square where an en passant capture is possible.

#### Board Representation API

    // Returns the position that results from making the given move in longform notation,
    // for example e7xd8=q+.
    Position makeMove(Move move)

### Move Generation

The move generator will provide a list of all the pseudo-legal moves available in the
provided position. Pseudo-legal moves are all the moves that a piece would be able to move
to without special rules like check. Illegal moves can then be filtered out of the position
and special moves like en passant or castling can be added.

#### Move Generator API

    pseudoLegalMoveList(const Position& pos)

### Evaluation

The evaluation function is used to determine how good the position is for a particular
side. The IcoChess evaluation function will take into account the 5 elements of chess:
Time, Space, Material, Pawn Structure, and King Safety.

### Search

The search function uses all the other components to look for possible good moves and
ultimately decide of the move to make. Traverses a game tree that represent all the possible
variations that the game could proceed with. 
