#pragma once
#ifndef GAME_H
#define GAME_H
// change chessgame to game

#include "Menu.h"
#include "Board.h"

class Game : public Menu
{
public:
    Game(int screenWidth, int screenHeight, const char* GameTitle, Vector2 initPosition);
    ~Game();
    void RunGame();
    void UpdateGame();
    void DrawGame();

    Board board;
    Vector2 selectedPos = { -1, -1 };  // position of the selected piece.

};

#endif // GAME_H