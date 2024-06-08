#ifndef MEOWCHESS_KNIGHT_H
#define MEOWCHESS_KNIGHT_H

#include "Piece.h"
#include "Board.h"

class Knight :
    public Piece
{
    Knight(Position position, PIECE_COLOR color): Piece(position, color, PIECE_TYPE::KNIGHT) {}

    std::vector<Move> GetPossibleMoves(const Board& board) override;
};

#endif //MEOWCHESS_KNIGHT_H