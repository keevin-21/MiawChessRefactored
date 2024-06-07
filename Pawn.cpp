#include "Pawn.h"

void Pawn::DoMove(const Move& move)
{
	if(move.type == MOVES::DOUBLE_STEP)
	{
		availableDoubleStep = true;
	}
	else
	{
		availableDoubleStep = false;
	}

	Piece::DoMove(move);
}

std::vector<Move> Pawn::GetPossibleMoves(const Board& board)
{
	std::vector<Move> possibleMoves;

	// If black, can only move down. Else, can only move up.


}
