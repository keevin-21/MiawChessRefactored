#include "Bishop.h"

std::vector<Move> Bishop::GetPossibleMoves(const Board& board)
{
	std::vector<Move> possibleMoves;

	ValidMoves(board, possibleMoves, { position.i - 1, position.j - 1 }, -1, -1);
	ValidMoves(board, possibleMoves, { position.i - 1, position.j + 1 }, -1, 1);
	ValidMoves(board, possibleMoves, { position.i + 1, position.j - 1 }, 1, -1);
	ValidMoves(board, possibleMoves, { position.i + 1, position.j + 1 }, 1, 1);

	return possibleMoves;
}

void Bishop::ValidMoves(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
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
