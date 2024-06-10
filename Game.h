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

    /*
    int screenWidth;
    int screenHeight;
    Vector2 circlePosition;
    int circleRadius;
    void Update();
    void Draw();*/
};

#endif // GAME_H