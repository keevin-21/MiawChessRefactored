#include "Rook.h"

// Refactorizaci�n utilizando el patr�n Strategy para modularizar las direcciones de movimiento.
// La funci�n AddMovesInDirection permite que el c�digo sea m�s flexible y reutilizable al delegar la l�gica del movimiento 
// en diferentes direcciones (arriba, abajo, izquierda, derecha).

std::vector<Move> Rook::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // El Rook se mueve en 4 direcciones: arriba, abajo, izquierda, derecha.
    // Cada direcci�n se maneja por la funci�n AddMovesInDirection.
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j }, -1, 0); // Up
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j }, 1, 0);  // Down
    AddMovesInDirection(board, possibleMoves, { position.i, position.j - 1 }, 0, -1); // Left
    AddMovesInDirection(board, possibleMoves, { position.i, position.j + 1 }, 0, 1);  // Right

    return possibleMoves;
}

// Funci�n que gestiona la adici�n de movimientos en una direcci�n espec�fica.
// Usamos iIncrease y jIncrease para ajustar el movimiento en las direcciones correspondientes.
void Rook::AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    // Iteramos mientras las posiciones est�n dentro de los l�mites del tablero
    while (board.IsPositionWithinLimits(pos))
    {
        const Piece* pieceAtPos = board.At(pos);

        if (pieceAtPos == nullptr)
        {
            possibleMoves.push_back({ MOVES::STEP, pos });
        }
        else
        {
            // Si la pieza en la posici�n tiene un color diferente, se puede atacar
            if (pieceAtPos->color != color)
            {
                possibleMoves.push_back({ MOVES::ATTACK, pos });
            }
            break;
        }

        // Continuamos movi�ndonos en la direcci�n especificada
        pos.i += iIncrease;
        pos.j += jIncrease;
    }
}
