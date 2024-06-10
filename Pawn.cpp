#include "Pawn.h"

void Pawn::DoMove(const Move& move)
{
	if(move.type == MOVES::DOUBLE_STEP)
	{
		didDoubleStep = true;
	}
	else
	{
		didDoubleStep = false;
	}

	Piece::DoMove(move);
}

std::vector<Move> Pawn::GetPossibleMoves(const Board& board)
{
	std::vector<Move> possibleMoves;

	// If black, can only move down. Else, can only move up.
	Position step = { position.i + (color == PIECE_COLOR::C_BLACK? +1 : -1), position.j };

	if(!board.At(step))
	{
		possibleMoves.push_back({ MOVES::STEP, step });
	}

	// If the pawn hasn't moved yet, it can move two steps.
	Position doubleStep = { position.i + (color == PIECE_COLOR::C_BLACK? +2 : -2), position.j };

	if(!board.At(doubleStep) && !this->hasMoved)
	{
		possibleMoves.push_back({ MOVES::DOUBLE_STEP, doubleStep });
	}

	// Check if pawn can capure.
	int attackDirection = position.i +(color == PIECE_COLOR::C_WHITE? -1 : 1);

	Position leftAttack = { attackDirection, position.j - 1 };
	Position rightAttack = { attackDirection, position.j + 1 };

	if(board.At(leftAttack) && board.At(leftAttack)->color != color)
	{
		possibleMoves.push_back({ MOVES::ATTACK, leftAttack });
	}

	if(board.At(rightAttack) && board.At(rightAttack)->color != color)
	{
		possibleMoves.push_back({ MOVES::ATTACK, rightAttack });
	}

	// Check en passant (left).
	Position leftEnPassant = { attackDirection, position.j - 1 };

	if (IsEnPassantAvailable(board, { position.i, position.j - 1 }, leftEnPassant))
		{
		possibleMoves.push_back({ MOVES::EN_PASSANT, leftEnPassant });
		}

	// Check for en passant (right).
	Position rightEnPassant = { attackDirection, position.j + 1 };
	
	if (IsEnPassantAvailable(board, {position.i, position.j + 1}, rightEnPassant))
	{
		possibleMoves.push_back({ MOVES::EN_PASSANT, rightEnPassant });
	}

	// Check promotion zone.
	for(Move& move : possibleMoves)
	{
		if(IsInPromotionPos(move.position))
		{
			if (move.type == MOVES::ATTACK)
			{
				move.type = MOVES::ATTACK_PROMOTION;
			}
			else if (move.type == MOVES::STEP)
			{
				move.type = MOVES::PROMOTION;
			}
		}
	}
	
	return possibleMoves;
}

bool Pawn::IsInPromotionPos(const Position& position)
{
	return (position.i == 0 && color == PIECE_COLOR::C_WHITE || position.i == 7 && color == PIECE_COLOR::C_BLACK);
}

bool Pawn::IsEnPassantAvailable(const Board& board, const Position& piecePosition, const Position& attackPosition)
{
	Piece* piece = board.At(piecePosition);


	if (!board.At(attackPosition) && piece && piece->color != color && piece->type == PIECE_TYPE::PAWN)
	{
		Pawn* pawn = (Pawn*)piece;

		if (pawn->didDoubleStep && pawn == board.GetLastMovedPiece())
		{
			return true;
		}
	}

	return false;
}