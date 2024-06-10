#ifndef MEOWCHESS_MENU_H
#define MEOWCHESS_MENU_H

#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include "raygui.h"
#include <string>
#include <iostream>
#include <map>

using std::string;
using std::map;

enum MENU_STATE
{
    MS_START,
    MS_NAMES,
    MS_GAME
};

class Menu
{
public:
    const static int WINDOW_WIDTH = 1280;
    const static int WINDOW_HEIGHT = 720;

    const static string TEXTURES_PATH;
    const static string SOUNDS_PATH;
    const static string ASSETS_PATH;
    const static string FONTS_PATH;

    Menu();
    ~Menu();

    void Run();
    void Deinit();
    bool IsGameStarting() const;

    const char* GetPlayer1Name() const { return player1Name; }
    const char* GetPlayer2Name() const { return player2Name; } 

private:
    MENU_STATE currentState;

    // Player names
    char player1Name[20];
    char player2Name[20];
    int currentInputPlayer;
    bool showPlayer1Notice = false;
    bool showPlayer2Notice = false;

    // Textures and sounds maps
    map<string, Texture2D> textures;
    map<string, Sound> sounds;
    map<string, Font> fonts;

    // Music
    bool musicPlaying;

    // Resource loading
    void LoadTextures();
    void LoadSounds();
    void LoadFonts();

    // Utility methods
    void Update();
    void Draw();
    void DrawStartScreen();
    void DrawNamesScreen();

    // Music Settings
    void PlayMusic();
    void StopMusic();

    // Button state
    bool dragWindow;
    bool exitWindow;
};

#endif // MEOWCHESS_MENU_H