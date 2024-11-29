#ifndef MEOWCHESS_ROOK_H
#define MEOWCHESS_ROOK_H

#include "Piece.h"

class Rook :
    public Piece
{
public:
    Rook(Position position, PIECE_COLOR color) : Piece(position, color, PIECE_TYPE::ROOK) {}
    std::vector<Move> GetPossibleMoves(const Board& board) override;

private:
    // Función para añadir movimientos en una dirección específica
    void AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease);
};

#endif //MEOWCHESS_ROOK_H
