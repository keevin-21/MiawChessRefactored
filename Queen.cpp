#include "Queen.h"

// Refactorizaci�n realizada aplicando el patr�n de dise�o Strategy para delegar las direcciones de los movimientos.
// La funci�n AddMovesInDirection permite que el c�digo sea m�s flexible y extensible para agregar nuevas estrategias de movimiento.
// Este patr�n mejora la legibilidad y separa la l�gica de movimiento de la pieza de su comportamiento principal.

std::vector<Move> Queen::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // Cada direcci�n es tratada como una estrategia de movimiento separada.
    // La funci�n AddMovesInDirection delega la verificaci�n de las posiciones en las direcciones especificadas.

    // Up.
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j }, -1, 0);
    // Up-right.
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j + 1 }, -1, 1);
    // Right.
    AddMovesInDirection(board, possibleMoves, { position.i, position.j + 1 }, 0, 1);
    // Down-right.
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j + 1 }, 1, 1);
    // Down.
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j }, 1, 0);
    // Down-left.
    AddMovesInDirection(board, possibleMoves, { position.i + 1, position.j - 1 }, 1, -1);
    // Left.
    AddMovesInDirection(board, possibleMoves, { position.i, position.j - 1 }, 0, -1);
    // Up-left.
    AddMovesInDirection(board, possibleMoves, { position.i - 1, position.j - 1 }, -1, -1);

    return possibleMoves;
}

// Refactorizaci�n para extraer la l�gica de verificaci�n de movimientos en una funci�n separada que se encarga de
// explorar las posiciones en una direcci�n espec�fica. La direcci�n est� determinada por los par�metros de incremento.
// Esto permite modificar o agregar nuevas estrategias de movimiento sin modificar el comportamiento principal de la pieza.

void Queen::AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    // Se itera por la direcci�n especificada y se agregan los movimientos v�lidos hasta que se encuentre una pieza.
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
