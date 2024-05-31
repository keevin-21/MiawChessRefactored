#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include "raygui.h"

enum class GameState {
    MENU,
    GAME
};

class Menu
{
public:

    Menu(int width, int height, const char* gameTitle, Vector2 initPosition);
    void Init();
    ~Menu() { Deinit(); }
    void Run();
    void Deinit();
    void Update();
    void Draw();

    int screenWidth;
    int screenHeight;
    const char* windowTitle;
    Vector2 mousePosition;
    Vector2 windowPosition;
    Vector2 panOffset;
    bool dragWindow;
    bool exitWindow;
    bool startbutton;

    // variables
    // int centerPositionX;
    GameState currentstate;
};