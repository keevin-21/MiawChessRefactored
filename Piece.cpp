#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

// Constructor de la pieza
Piece::Piece(Position position, PIECE_COLOR color, PIECE_TYPE type) : position(position), color(color), type(type) {
    GenerateName();  // Llamada al m�todo privado para generar el nombre
}

// M�todo para generar el nombre de la pieza (combinaci�n de color y tipo de pieza)
void Piece::GenerateName() {
    std::string colorPrefix = (color == PIECE_COLOR::C_WHITE) ? "w" : "b";
    std::string pieceCharacter = GetPieceCharacter(type);
    this->name = colorPrefix + pieceCharacter;
}

// M�todo para mover la pieza
void Piece::DoMove(const Move& move) {
    hasMoved = true;
    position = move.position;
}

// M�todos para obtener informaci�n sobre la pieza
Position Piece::GetPosition() const {
    return position;
}

std::string Piece::GetName() const {
    return name;
}

bool Piece::HasMoved() const {
    return hasMoved;
}

// M�todo est�tico para crear una pieza espec�fica seg�n su tipo
Piece* Piece::CreatePiece(PIECE_TYPE type, const Position& position, PIECE_COLOR color) {
    switch (type) {
    case PAWN: return new Pawn(position, color);
    case ROOK: return new Rook(position, color);
    case KNIGHT: return new Knight(position, color);
    case BISHOP: return new Bishop(position, color);
    case QUEEN: return new Queen(position, color);
    case KING: return new King(position, color);
    default: return nullptr;
    }
}

// M�todo est�tico para obtener el color inverso de una pieza
PIECE_COLOR Piece::GetInverseColor(PIECE_COLOR color) {
    return (color == PIECE_COLOR::C_WHITE) ? PIECE_COLOR::C_BLACK : PIECE_COLOR::C_WHITE;
}

// M�todo est�tico para obtener el car�cter correspondiente al tipo de pieza
std::string Piece::GetPieceCharacter(PIECE_TYPE type) {
    switch (type) {
    case PAWN: return "p";
    case ROOK: return "r";
    case KNIGHT: return "n";
    case BISHOP: return "b";
    case QUEEN: return "q";
    case KING: return "k";
    default: return "";
    }
}

// M�todo para actualizar la posici�n de la pieza
void Piece::SetPosition(const Position& newPosition) {
    position = newPosition;
}
