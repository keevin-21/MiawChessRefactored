#include "Game.h"

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), circleRadius(20) 
{ // init windows and setTargetFPS
    circlePosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    InitWindow(screenWidth, screenHeight, "Mi Juego con Raylib");
    SetTargetFPS(60);
}

Game::~Game() 
{
    // close window
    CloseWindow();
}

void Game::Run() 
{
    // while !Windows should close and update with draw function. 
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void Game::Update() 
{
    // Controls of the game, keys.
    if (IsKeyDown(KEY_RIGHT)) circlePosition.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) circlePosition.x -= 2.0f;
    if (IsKeyDown(KEY_UP)) circlePosition.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) circlePosition.y += 2.0f;
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // draw object and function
    DrawCircleV(circlePosition, circleRadius, MAROON);
    EndDrawing();
}