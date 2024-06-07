#include "Board.h"
#include "Pawn.h"
#include <string>
#include <map>

Board::Board(const Board& other) {
    Clear();

    for (Piece* whitePiece : other.whitePieces) {
        Piece* newPiece = Piece::CreatePieceByType(whitePiece->type, whitePiece->GetPosition(), whitePiece->color);
        Add(newPiece);
    }

    for (Piece* blackPiece : other.blackPieces) {
        Piece* newPiece = Piece::CreatePieceByType(blackPiece->type, blackPiece->GetPosition(), blackPiece->color);
        Add(newPiece);
    }
}

Board::~Board() {
	Clear();
}

void Board::Init()
{
    // Black pieces.
    for (int j = 0; j < 8; j++)
	{
		Add(new Pawn({ 1, j }, PIECE_COLOR::C_BLACK));
	}

    // White pieces.
    for (int j = 0; j < 8; j++)
    {
        Add(new Pawn({ 6, j }, PIECE_COLOR::C_WHITE));
    }
}

Piece* Board::At(const Position& position) const
{

}


void Board::Add(Piece* piece)
{
    if(piece->color == PIECE_COLOR::C_WHITE)
	{
		whitePieces.push_back(piece);
	}
	else
	{
		blackPieces.push_back(piece);
	}
}

void Board::Destroy(const Position& position)
{
    for(unsigned int i = 0; i < whitePieces.size(); i++)
    {
        if (whitePieces[i]->GetPosition().i == position.i && whitePieces[i]->GetPosition().j == position.j)
        {
            delete whitePieces[i];
            whitePieces.erase(whitePieces.begin() + i);
            return;
        }
    }

    for (unsigned int i = 0; i < blackPieces.size(); i++)
    {
        if(blackPieces[i]->GetPosition().i == position.i && blackPieces[i]->GetPosition().j == position.j)
        {
			delete blackPieces[i];
			blackPieces.erase(blackPieces.begin() + i);
			return;
		}
    }
}

void Board::Clear()
{
    for (auto& whitePiece : whitePieces)
    {
        delete whitePiece;
    }

    for (auto& blackPiece : blackPieces)
    {
        delete blackPiece;
    }

    whitePieces.clear();
    blackPieces.clear();
}

bool Board::IsPositionWithinLimits(const Position& position) const
{
    return position.i >= 0 && position.i < 8 && position.j >= 0 && position.j < 8;
}

std::vector<Piece*> Board::GetPiecesByColor(PIECE_COLOR color) const
{
    if (color == PIECE_COLOR::C_WHITE)
    {
        return whitePieces;
    }
    else
    {
        return blackPieces;
    }
}

Piece* Board::GetLastMovedPiece() const
{
    return At(lastMovedPiecePosition);
}

void Board::DoMove(Piece* piece, const Move& move)
{
    // Delete piece if attack or en passant.
    if(move.type == MOVES::ATTACK || move.type == MOVES::ATTACK_PROMOTION)
    {
        Destroy(move.position);
    }
    else if (move.type == MOVES::EN_PASSANT)
    {
        Destroy({ piece->GetPosition().i, move.position.j });
    }

    // Move piece in case of castling, also move rook.
    if(move.type == MOVES::SHORT_CASTLE)
	{
		DoShortCastling(piece, move);
	}
    else if (move.type == MOVES::LONG_CASTLE)
    {
        DoLongCastling(piece, move);
    }
    else
    {
        piece->DoMove(move);
    }

    lastMovedPiecePosition = piece->GetPosition();
}

bool Board::MoveLeadsToCheck(Piece* piece, const Move& move)
{
    Board boardCopy = *this;
    Piece* pieceCopy = boardCopy.At(piece->GetPosition());
}

bool Board::IsInCheck(PIECE_COLOR color)
{
    std::vector<Piece*> enemyPieces = GetPiecesByColor(Piece::GetInverseColor(color));

    for (Piece* piece : enemyPieces)
    {
        for (const Move& move : piece->GetPossibleMoves(*this))
        {
            Piece* pieceAtMovePosition = At(move.position);

            bool positionContainsKing = pieceAtMovePosition &&
                pieceAtMovePosition->color == color &&
                pieceAtMovePosition->type == PIECE_TYPE::KING;

            bool moveIsAttack = move.type == MOVES::ATTACK || move.type == MOVES::ATTACK_PROMOTION;

            // If the enemy piece is attacking my king, the king is in check.
            if (positionContainsKing && moveIsAttack)
            {
                return true;
            }
        }
    }

    return false;
}

void Board::DoShortCastling(Piece* selectedPiece, const Move& move)
{
    Piece* rook = At({ selectedPiece->GetPosition().i, 7 });

    selectedPiece->DoMove(move);
    rook->DoMove({ MOVES::STEP, rook->GetPosition().i, rook->GetPosition().j - 2});
}

void Board::DoLongCastling(Piece* selectedPiece, const Move& move)
{
    Piece* rook = At({ selectedPiece->GetPosition().i, 0 });

	selectedPiece->DoMove(move);
	rook->DoMove({ MOVES::STEP, rook->GetPosition().i, rook->GetPosition().j + 3 });
}

