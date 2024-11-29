#ifndef MEOWCHESS_BISHOP_H
#define MEOWCHESS_BISHOP_H

#include "Piece.h"
#include "Board.h"

class Bishop :
    public Piece
{
public:
    Bishop(Position position, PIECE_COLOR color) : Piece(position, color, PIECE_TYPE::BISHOP) {}
    std::vector<Move> GetPossibleMoves(const Board& board) override;

private:
    // Método para añadir movimientos en una dirección específica.
    void AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease);
};

#endif //MEOWCHESS_BISHOP_H
