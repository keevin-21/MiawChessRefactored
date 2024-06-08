#ifndef MEOWCHESS_QUEEN_H
#define MEOWCHESS_QUEEN_H

#include "Piece.h"
#include "Board.h"

class Queen :
    public Piece
{
public:
    Queen(Position position, PIECE_COLOR color) : Piece(position, color, PIECE_TYPE::QUEEN) {}
    std::vector<Move> GetPossibleMoves(const Board& board) override;

private:
    void ValidMoves(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease);
};

#endif //MEOWCHESS_QUEEN_H