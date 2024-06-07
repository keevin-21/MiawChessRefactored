#ifndef MEOWCHESS_PAWN_H
#define MEOWCHESS_PAWN_H

#include "Piece.h"
#include "Board.h"

#include "Piece.h"
class Pawn :
    public Piece
{
public:
    Pawn(Position position, PIECE_COLOR color) : Piece(position, color, PIECE_TYPE::PAWN) {}

    void DoMove(const Move& move) override;
    std::vector<Move> GetPossibleMoves(const Board& board) override;

    bool availableDoubleStep = false;

private:
    bool IsInPromotionZone(const Position& position);
    bool IsEnPassantAvailable(const Board& board, const Position& attackPosition);
};

#endif //MEOWCHESS_PAWN_H