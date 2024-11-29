#include "Bishop.h"

// Refactorización aplicada utilizando el patrón Strategy para delegar la lógica de los movimientos en direcciones específicas.
// La función AddMovesInDirection permite modularizar el cálculo de movimientos, mejorando la flexibilidad y reutilización del código.

std::vector<Move> Bishop::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // El Bishop se mueve en 4 direcciones diagonales. Cada dirección es manejada por AddMovesInDirection.
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j - 1 }, -1, -1); // Up-left
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j + 1 }, -1, 1);  // Up-right
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j - 1 }, 1, -1);  // Down-left
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j + 1 }, 1, 1);   // Down-right

    return possibleMoves;
}

// Refactorización para extraer la lógica de movimientos en una función separada que permite explorar las posiciones
// en una dirección específica hasta que una pieza o los límites del tablero lo impidan.

void Bishop::AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    // Se exploran las posiciones en la dirección especificada por los incrementos iIncrease y jIncrease
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
