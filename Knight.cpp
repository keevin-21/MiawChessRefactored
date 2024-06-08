#include "Knight.h"

std::vector<Move> Knight::GetPossibleMoves(const Board& board)
{
    // 8 possible moves.
    std::vector<Position> possiblePositions = {
        
        // 2 up, 1 right.
        {position.i -2, position.j - 1},
        // 2 up, 1 left.
        {position.i -2, position.j + 1},

        // 2 down, 1 right.
        {position.i +2, position.j - 1},
        // 2 down, 1 left.
        {position.i +2, position.j + 1},

        // 2 left, 1 up.
        {position.i -1, position.j - 2},
        // 2 left, 1 down.
        {position.i +1, position.j - 2},

        // 2 right, 1 up.
        {position.i -1, position.j + 2},
        // 2 right, 1 down.
        {position.i +1, position.j + 2}
    };

    std::vector<Move> possibleMoves;
    for (const Position& position : possiblePositions)
    {
        if (board.IsPositionWithinLimits(position))
        {
            if (!board.At(position))
            {
                possibleMoves.push_back({ MOVES::STEP, position });
            }
            else if (board.At(position)->color != color)
            {
                possibleMoves.push_back({ MOVES::ATTACK, position });
            }
        }
    }

    return possibleMoves;
}
