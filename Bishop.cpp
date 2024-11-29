#include "Bishop.h"

// Refactorizaci�n aplicada utilizando el patr�n Strategy para delegar la l�gica de los movimientos en direcciones espec�ficas.
// La funci�n AddMovesInDirection permite modularizar el c�lculo de movimientos, mejorando la flexibilidad y reutilizaci�n del c�digo.

std::vector<Move> Bishop::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // El Bishop se mueve en 4 direcciones diagonales. Cada direcci�n es manejada por AddMovesInDirection.
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j - 1 }, -1, -1); // Up-left
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j + 1 }, -1, 1);  // Up-right
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j - 1 }, 1, -1);  // Down-left
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j + 1 }, 1, 1);   // Down-right

    return possibleMoves;
}

// Refactorizaci�n para extraer la l�gica de movimientos en una funci�n separada que permite explorar las posiciones
// en una direcci�n espec�fica hasta que una pieza o los l�mites del tablero lo impidan.

void Bishop::AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    // Se exploran las posiciones en la direcci�n especificada por los incrementos iIncrease y jIncrease
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
