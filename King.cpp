#include "King.h"

// Refactorización aplicada al método GetPossibleMoves.
// El código de cálculo de movimientos ahora está delegado al nuevo método CalculateMoves,
// que se enfoca exclusivamente en obtener los movimientos del rey.
// Esto mejora la legibilidad y facilita la modificación futura.

std::vector<Move> King::GetPossibleMoves(const Board& board)
{
    std::vector<Move> possibleMoves = CalculateMoves(board);

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

    return possibleMoves;
}

// Método privado para encapsular la lógica de verificación de movimientos del rey.
// Esta refactorización permite un código más limpio y modular, siguiendo el principio de responsabilidad única.

std::vector<Move> King::CalculateMoves(const Board& board)
{
    std::vector<Position> possiblePositions =
    {
        {position.i - 1, position.j},
        {position.i - 1, position.j + 1},
        {position.i, position.j + 1},
        {position.i + 1, position.j + 1},
        {position.i + 1, position.j},
        {position.i + 1, position.j - 1},
        {position.i, position.j - 1},
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

    // Eliminar movimientos fuera de los límites del tablero. Este paso se realiza después
    // de haber calculado los posibles movimientos, ya que la validación de límites es independiente
    // del cálculo inicial de las posiciones.
    for (int i = possibleMoves.size() - 1; i >= 0; i--)
    {
        if (!board.IsPositionWithinLimits(possibleMoves[i].position))
        {
            possibleMoves.erase(possibleMoves.begin() + i);
        }
    }

    return possibleMoves;
}

// La función IsCastlingAvailable no sufrió cambios, ya que cumple una única función clara
// que no necesita refactorización adicional en este momento.

bool King::IsCastlingAvailable(const Board& board, const Position& rookPosition, const std::vector<Position>& mediumPositions)
{
    Piece* piece = board.At(rookPosition);

    if (!piece || piece->color != color || piece->type != PIECE_TYPE::ROOK || piece->HasMoved() || hasMoved)
    {
        return false;
    }

    for (const Position& mediumPosition : mediumPositions)
    {
        if (board.At(mediumPosition))
        {
            return false;
        }
    }

    return true;
}
