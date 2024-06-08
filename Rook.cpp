#include "Rook.h"

std::vector<Move> Rook::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // Check all possible moves in all directions.
    
    // Up
    ValidMoves(board, possibleMoves, {position.i - 1, position.j }, -1, 0);
     
    // Down
    ValidMoves(board, possibleMoves, {position.i + 1, position.j }, 1, 0);

    // Left
    ValidMoves(board, possibleMoves, {position.i, position.j - 1 }, 0, -1);

    // Right
    ValidMoves(board, possibleMoves, {position.i, position.j + 1 }, 0, 1);
}

void Rook::ValidMoves(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    while (board.IsPositionWithinLimits(pos))
    {
        if (!board.At(pos))
        {
            possibleMoves.push_back({ MOVES::STEP, pos });
            pos.i += iIncrease;
            pos.j += jIncrease;
        }
        else if (board.At(pos) && board.At(pos)->color != color)
        {
            possibleMoves.push_back({ MOVES::ATTACK, pos });
        }
		else
		{
			break;
		}
    }
}
