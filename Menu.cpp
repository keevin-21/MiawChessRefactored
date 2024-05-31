#define RAYGUI_IMPLEMENTATION
#include "Menu.h"

void Menu::Init()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, windowTitle);
    SetWindowPosition(windowPosition.x, windowPosition.y);
    dragWindow = false;
    exitWindow = false;
    SetTargetFPS(60);
    GuiLoadStyle("style_jungle.rgs");
}


Menu::Menu(int width, int height, const char* gameTitle, Vector2 initPosition)
    : screenWidth(width), screenHeight(height), windowTitle(gameTitle), windowPosition(initPosition)
{
    Init();
}

void Menu::Run()
{
    while (!exitWindow && !WindowShouldClose())
    {
        Update();
        Draw();
    }
}

void Menu::Deinit()
{
    CloseWindow();
}

void Menu::Update()
{
    mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !dragWindow) {
        if (CheckCollisionPointRec(mousePosition, Rectangle{ 0.0f, 0.0f, static_cast<float>(screenWidth), 20.0f })) {
            dragWindow = true;
            panOffset = mousePosition;
        }
    }

    if (dragWindow) {
        windowPosition.x += (mousePosition.x - panOffset.x);
        windowPosition.y += (mousePosition.y - panOffset.y);
        SetWindowPosition(static_cast<int>(windowPosition.x), static_cast<int>(windowPosition.y));

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragWindow = false;
    }

    if (GuiButton(Rectangle{ 305.0f, 400.0f, 100, 40 }, "START GAME"))
    {
        // link this with another screen.
        ClearBackground(RAYWHITE);
    }

    // Create an instance where I clicked the start button.
}

void Menu::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    exitWindow = GuiWindowBox(Rectangle{ 0.0f, 0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight) }, "#198# CHESSY GAME");
    // After this, begin drawwing objects.
    GuiButton(Rectangle{ 305.0f, 400.0f, 100, 40 }, "START GAME");
    DrawText("CHESSY GAME", 190, 200, 50, BLACK);
    EndDrawing();
}