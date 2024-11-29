#include "Rook.h"

// Refactorización utilizando el patrón Strategy para modularizar las direcciones de movimiento.
// La función AddMovesInDirection permite que el código sea más flexible y reutilizable al delegar la lógica del movimiento 
// en diferentes direcciones (arriba, abajo, izquierda, derecha).

std::vector<Move> Rook::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // El Rook se mueve en 4 direcciones: arriba, abajo, izquierda, derecha.
    // Cada dirección se maneja por la función AddMovesInDirection.
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j }, -1, 0); // Up
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j }, 1, 0);  // Down
    AddMovesInDirection(board, possibleMoves, { position.i, position.j - 1 }, 0, -1); // Left
    AddMovesInDirection(board, possibleMoves, { position.i, position.j + 1 }, 0, 1);  // Right

    return possibleMoves;
}

// Función que gestiona la adición de movimientos en una dirección específica.
// Usamos iIncrease y jIncrease para ajustar el movimiento en las direcciones correspondientes.
void Rook::AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    // Iteramos mientras las posiciones estén dentro de los límites del tablero
    while (board.IsPositionWithinLimits(pos))
    {
        const Piece* pieceAtPos = board.At(pos);

        if (pieceAtPos == nullptr)
        {
            possibleMoves.push_back({ MOVES::STEP, pos });
        }
        else
        {
            // Si la pieza en la posición tiene un color diferente, se puede atacar
            if (pieceAtPos->color != color)
            {
                possibleMoves.push_back({ MOVES::ATTACK, pos });
            }
            break;
        }

        // Continuamos moviéndonos en la dirección especificada
        pos.i += iIncrease;
        pos.j += jIncrease;
    }
}
