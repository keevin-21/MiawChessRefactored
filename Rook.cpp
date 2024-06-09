#include "Rook.h"

std::vector<Move> Rook::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // Up
    ValidMoves(board, possibleMoves, { position.i - 1, position.j }, -1, 0);
    // Down
    ValidMoves(board, possibleMoves, { position.i + 1, position.j }, 1, 0);
    // Left
    ValidMoves(board, possibleMoves, { position.i, position.j - 1 }, 0, -1);
    // Right
    ValidMoves(board, possibleMoves, { position.i, position.j + 1 }, 0, 1);

    return possibleMoves;
}

void Rook::ValidMoves(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    while (board.IsPositionWithinLimits(pos))
    {
        const Piece* pieceAtPos = board.At(pos);

        if (pieceAtPos == nullptr)
        {
            possibleMoves.push_back({ MOVES::STEP, pos });
        }
        else
        {
            if (pieceAtPos->color != color)
            {
                possibleMoves.push_back({ MOVES::ATTACK, pos });
            }
            break;
        }

        pos.i += iIncrease;
        pos.j += jIncrease;
    }
}
