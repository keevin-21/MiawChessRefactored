#include "Pawn.h"

// M�todo para mover el pe�n y gestionar el estado de la doble pasada
void Pawn::DoMove(const Move& move)
{
    if (move.type == MOVES::DOUBLE_STEP)
    {
        didDoubleStep = true;
    }
    else
    {
        didDoubleStep = false;
    }

    Piece::DoMove(move);
}

// M�todo que gestiona todos los movimientos posibles del pe�n
std::vector<Move> Pawn::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // 1. Movimiento hacia adelante (1 paso)
    AddStepMove(board, possibleMoves);

    // 2. Movimiento doble (solo si el pe�n no se ha movido antes)
    AddDoubleStepMove(board, possibleMoves);

    // 3. Movimientos de ataque (a las posiciones diagonales)
    AddAttackMoves(board, possibleMoves);

    // 4. Movimientos de en passant (si est�n disponibles)
    AddEnPassantMoves(board, possibleMoves);

    // 5. Movimiento de promoci�n (si est� en la zona de promoci�n)
    AddPromotionMoves(possibleMoves);

    return possibleMoves;
}

// Verifica el movimiento de un paso hacia adelante (si est� libre)
void Pawn::AddStepMove(const Board& board, std::vector<Move>& possibleMoves)
{
    Position step = { position.i + (color == PIECE_COLOR::C_BLACK ? +1 : -1), position.j };
    if (!board.At(step))
    {
        possibleMoves.push_back({ MOVES::STEP, step });
    }
}

// Verifica el movimiento doble (si no se ha movido antes)
void Pawn::AddDoubleStepMove(const Board& board, std::vector<Move>& possibleMoves)
{
    Position doubleStep = { position.i + (color == PIECE_COLOR::C_BLACK ? +2 : -2), position.j };
    if (!board.At(doubleStep) && !this->hasMoved)
    {
        possibleMoves.push_back({ MOVES::DOUBLE_STEP, doubleStep });
    }
}

// Verifica los movimientos de ataque en las posiciones diagonales
void Pawn::AddAttackMoves(const Board& board, std::vector<Move>& possibleMoves)
{
    int attackDirection = position.i + (color == PIECE_COLOR::C_WHITE ? -1 : 1);

    Position leftAttack = { attackDirection, position.j - 1 };
    Position rightAttack = { attackDirection, position.j + 1 };

    if (board.At(leftAttack) && board.At(leftAttack)->color != color)
    {
        possibleMoves.push_back({ MOVES::ATTACK, leftAttack });
    }

    if (board.At(rightAttack) && board.At(rightAttack)->color != color)
    {
        possibleMoves.push_back({ MOVES::ATTACK, rightAttack });
    }
}

// Verifica si el movimiento de en passant est� disponible
void Pawn::AddEnPassantMoves(const Board& board, std::vector<Move>& possibleMoves)
{
    int attackDirection = position.i + (color == PIECE_COLOR::C_WHITE ? -1 : 1);

    Position leftEnPassant = { attackDirection, position.j - 1 };
    if (IsEnPassantAvailable(board, { position.i, position.j - 1 }, leftEnPassant))
    {
        possibleMoves.push_back({ MOVES::EN_PASSANT, leftEnPassant });
    }

    Position rightEnPassant = { attackDirection, position.j + 1 };
    if (IsEnPassantAvailable(board, { position.i, position.j + 1 }, rightEnPassant))
    {
        possibleMoves.push_back({ MOVES::EN_PASSANT, rightEnPassant });
    }
}

// Verifica si el pe�n est� en la zona de promoci�n
void Pawn::AddPromotionMoves(std::vector<Move>& possibleMoves)
{
    for (Move& move : possibleMoves)
    {
        if (IsInPromotionPos(move.position))
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
}

// Verifica si la posici�n est� en la fila de promoci�n (fila 0 o 7 dependiendo del color)
bool Pawn::IsInPromotionPos(const Position& position)
{
    return (position.i == 0 && color == PIECE_COLOR::C_WHITE || position.i == 7 && color == PIECE_COLOR::C_BLACK);
}

// Verifica si el movimiento de en passant est� disponible
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
