#ifndef MEOWCHESS_MOVES_H
#define MEOWCHESS_MOVES_H

#include "Position.h"
#include "PieceEnums.h" 
enum MOVES
{
    STEP,
    DOUBLE_STEP,
    ATTACK,
    SHORT_CASTLE,
    LONG_CASTLE,
    EN_PASSANT,
    PROMOTION,
    ATTACK_PROMOTION,
};

struct Move
{
    MOVES type;
    Position position;
    PIECE_COLOR pieceColor; // Cambiado a PIECE_COLOR
};

#endif // MEOWCHESS_MOVES_H
