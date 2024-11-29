#include "King.h"

// Refactorizaci�n aplicada al m�todo GetPossibleMoves.
// El c�digo de c�lculo de movimientos ahora est� delegado al nuevo m�todo CalculateMoves,
// que se enfoca exclusivamente en obtener los movimientos del rey.
// Esto mejora la legibilidad y facilita la modificaci�n futura.

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

// M�todo privado para encapsular la l�gica de verificaci�n de movimientos del rey.
// Esta refactorizaci�n permite un c�digo m�s limpio y modular, siguiendo el principio de responsabilidad �nica.

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

    // Eliminar movimientos fuera de los l�mites del tablero. Este paso se realiza despu�s
    // de haber calculado los posibles movimientos, ya que la validaci�n de l�mites es independiente
    // del c�lculo inicial de las posiciones.
    for (int i = possibleMoves.size() - 1; i >= 0; i--)
    {
        if (!board.IsPositionWithinLimits(possibleMoves[i].position))
        {
            possibleMoves.erase(possibleMoves.begin() + i);
        }
    }

    return possibleMoves;
}

// La funci�n IsCastlingAvailable no sufri� cambios, ya que cumple una �nica funci�n clara
// que no necesita refactorizaci�n adicional en este momento.

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
