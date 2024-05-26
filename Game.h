#pragma once
#ifndef GAME_H
#define GAME_H

#include "raylib.h"
class Game
{
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    void Run();

private:
    int screenWidth;
    int screenHeight;
    Vector2 circlePosition;
    int circleRadius;
    void Update();
    void Draw();
};

#endif // GAME_H