#include "Queen.h"

std::vector<Move> Queen::GetPossibleMoves(const Board& board)
{
	std::vector<Move> possibleMoves;

	// Up.
	ValidMoves(board, possibleMoves, { position.i - 1, position.j }, -1, 0);
	// Up-right.
	ValidMoves(board, possibleMoves, { position.i - 1, position.j + 1 }, -1, 1);
	// Right.
	ValidMoves(board, possibleMoves, { position.i, position.j + 1 }, 0, 1);
	// Down-right.
	ValidMoves(board, possibleMoves, { position.i + 1, position.j + 1 }, 1, 1);
	// Down.
	ValidMoves(board, possibleMoves, { position.i + 1, position.j }, 1, 0);
	// Down-left.
	ValidMoves(board, possibleMoves, { position.i + 1, position.j - 1 }, 1, -1);
	// Left.
	ValidMoves(board, possibleMoves, { position.i, position.j - 1 }, 0, -1);
	// Up-left.
	ValidMoves(board, possibleMoves, { position.i - 1, position.j - 1 }, -1, -1);

	return possibleMoves;
}

void Queen::ValidMoves(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
	while(board.IsPositionWithinLimits(pos))
	{
		if(!board.At(pos))
		{
			possibleMoves.push_back({ MOVES::STEP, pos });
			pos.i += iIncrease;
			pos.j += jIncrease;
		}
		else if (board.At(pos) && board.At(pos)->color != color)
		{
			break;
		}
		else
		{
			break;
		}
	}
}
