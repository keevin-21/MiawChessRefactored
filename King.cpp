#include "King.h"

std::vector<Move> King::GetPossibleMoves(const Board& board)
{
    std::vector<Position> possiblePositions =
    {
        // Up.
        {position.i -1, position.j},
        // Up-right.
        {position.i - 1, position.j + 1},
        // Right.
        {position.i, position.j + 1},
        // Down-right.
        {position.i + 1, position.j + 1},
        // Down.
        {position.i + 1, position.j},
        // Down-left.
        {position.i + 1, position.j - 1},
        // Left.
        {position.i, position.j - 1},
        // Up-left.
        {position.i - 1, position.j - 1}
    };
}

bool King::IsCastlingAvailable(const Board& board, const Position& rookPosition, const std::vector<Position>& mediumPositions)
{
    Piece* piece = board.At(rookPosition);
    
    if(!piece || piece->color != color || piece->type != PIECE_TYPE::ROOK || piece->HasMoved() || hasMoved)
    {
        return false;
    }

    for(const Position& mediumPosition : mediumPositions)
	{
		if(board.At(mediumPosition))
		{
			return false;
		}
	}
    
    return true;
}
