#include "Queen.h"

// Refactorización realizada aplicando el patrón de diseño Strategy para delegar las direcciones de los movimientos.
// La función AddMovesInDirection permite que el código sea más flexible y extensible para agregar nuevas estrategias de movimiento.
// Este patrón mejora la legibilidad y separa la lógica de movimiento de la pieza de su comportamiento principal.

std::vector<Move> Queen::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves;

    // Cada dirección es tratada como una estrategia de movimiento separada.
    // La función AddMovesInDirection delega la verificación de las posiciones en las direcciones especificadas.

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

// Refactorización para extraer la lógica de verificación de movimientos en una función separada que se encarga de
// explorar las posiciones en una dirección específica. La dirección está determinada por los parámetros de incremento.
// Esto permite modificar o agregar nuevas estrategias de movimiento sin modificar el comportamiento principal de la pieza.

void Queen::AddMovesInDirection(const Board& board, std::vector<Move>& possibleMoves, Position pos, int iIncrease, int jIncrease)
{
    // Se itera por la dirección especificada y se agregan los movimientos válidos hasta que se encuentre una pieza.
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
