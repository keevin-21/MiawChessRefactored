#ifndef MEOWCHESS_KING_H
#define MEOWCHESS_KING_H

#include "Piece.h"
#include "Board.h"

class King :
    public Piece
{
public:
    King(Position position, PIECE_COLOR color) : Piece(position, color, PIECE_TYPE::KING) {}

    // Refactorizado para encapsular la lógica de verificación de movimientos posibles.
    std::vector<Move> GetPossibleMoves(const Board& board) override;

private:
    bool IsCastlingAvailable(const Board& board, const Position& rookPosition, const std::vector<Position>& mediumPositions);

    // Método privado que maneja la lógica de posibles movimientos del rey.
    std::vector<Move> CalculateMoves(const Board& board);
};

#endif //MEOWCHESS_KING_H
