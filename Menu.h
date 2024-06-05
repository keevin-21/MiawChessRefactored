#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include "raygui.h"
#include <string>

// Class of game status, whether is the game screen or menu screen.

enum class GameState {
    MENU,
    GAME
};

class Menu
{
public:

    Menu(int width, int height, const char* gameTitle, Vector2 initPosition); // constructor
    void Init(); // initialize variables.
    ~Menu() { Deinit(); } // destructor and delete variables.
    void Run(); // run game. start it.
    void Deinit(); // delete variables
    void Update(); // realize changes on the game.
    void DrawBoardMenu(); // draw board menu.
    void Draw(); // draw menu.

    // Menu variables.
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
    GameState currentstate;
    std::string player1; // Player 1 name.
    char nameBuffer[21];  // Buffer to save the name of the player.

};