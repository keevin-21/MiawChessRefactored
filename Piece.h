#ifndef MEOWCHESS_PIECE_H
#define MEOWCHESS_PIECE_H

class Piece; // Forward declaration (circular dependency).

#include "raylib.h"
#include "Position.h"
#include "Board.h"
#include "Moves.h"
#include "PieceEnums.h"

#include <string>
#include <vector>

class Piece {
public:
    Piece(Position position, PIECE_COLOR color, PIECE_TYPE type);
    virtual ~Piece() = default;

    // Métodos estáticos para obtener la pieza, el color inverso y el caracter de la pieza
    static Piece* CreatePiece(PIECE_TYPE type, const Position& position, PIECE_COLOR color);
    static PIECE_COLOR GetInverseColor(PIECE_COLOR color);
    static std::string GetPieceCharacter(PIECE_TYPE type);

    virtual void DoMove(const Move& move);
    virtual std::vector<Move> GetPossibleMoves(const Board& board) = 0;

    Position GetPosition() const;
    std::string GetName() const;
    bool HasMoved() const;

    const PIECE_COLOR color;
    const PIECE_TYPE type;

    void SetPosition(const Position& newPosition);

protected:
    Position position;
    bool hasMoved = false;

private:
    std::string name;
    void GenerateName(); // Método privado para generar el nombre de la pieza
};

#endif //MEOWCHESS_PIECE_H
