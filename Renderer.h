#ifndef MEOWCHESS_RENDERER_H
#define MEOWCHESS_RENDERER_H

#include "raylib.h"
#include "Piece.h"
#include "Game.h"
#include "Moves.h" // Incluye la definición de Move
#include "Piece.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Renderer
{
public:
    static void Clear();
    static void RenderBackground();
    static void RenderPieces(const Board& board, const std::map<string, Texture>& textures);
    static void RenderPossibleMoves(const std::map<string, Texture>& textures, const std::vector<Move>& possibleMoves);
    static void RenderGuide();
    static void RenderPromotion(const std::map<string, Texture>& textures, PIECE_COLOR pawnColor);
    static void RenderInfo(int round, double timer);
    static void RenderEndGame(GAME_STATE gameState);
    static void MouseCursor(const Board& board, const std::vector<Move>& possibleMoves, PIECE_COLOR turn, bool inPromotion);

private:
    static string GetTextureFromMoveType(MOVES moveType);
    static Color GetShadeColor(PIECE_COLOR color);
    static PIECE_COLOR GetColorCell(const Position& cellPosition);
};

#endif //MEOWCHESS_RENDERER_H
