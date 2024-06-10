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

    std::vector<Move> possibleMoves;

    for (const Position& position : possiblePositions)
	{
		if (board.IsPositionWithinLimits(position))
		{
            if (!board.At(position))
            {
                possibleMoves.push_back({ MOVES::STEP, position });
            }
            else if (board.At(position) && board.At(position)->color != color) 
            {
                possibleMoves.push_back({ MOVES::ATTACK, position });
            }
		}
	}

    // Long castling. Left rook.
    if (IsCastlingAvailable(board, { position.i, 0 }, { {position.i, 1}, {position.i, 2}, {position.i, 3} }))
    {
        possibleMoves.push_back({ MOVES::LONG_CASTLE, {position.i, 2} });
    }

    // Long castling. Right rook.
    if (IsCastlingAvailable(board, { position.i, 7 }, { {position.i, 5}, {position.i, 6} }))
    {
        possibleMoves.push_back({ MOVES::SHORT_CASTLE, {position.i, 6} });
    }

    // Remove all moves that go out of the board.
    for (int i = possibleMoves.size() - 1; i >= 0; i--)
    {
        if (!board.IsPositionWithinLimits(possibleMoves[i].position))
        {
            possibleMoves.erase(possibleMoves.begin() + i);
        }
    }

    return possibleMoves;
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
