#include "Bishop.h"

std::vector<Move> Bishop::GetPossibleMoves(const Board& board)
{
	std::vector<Move> possibleMoves;
	
	
	
	return possibleMoves;
}

void Bishop::ValidMoves(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
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
