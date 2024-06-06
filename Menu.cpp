#define RAYGUI_IMPLEMENTATION
#include "Menu.h"

// Default constructor, initialize variables.
void Menu::Init()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, windowTitle);
    SetWindowPosition(windowPosition.x, windowPosition.y);
    dragWindow = false;
    exitWindow = false;
    SetTargetFPS(60);
    GuiLoadStyle("style_jungle.rgs"); // Load custom style.
    player1 = "";
    memset(nameBuffer, 0, sizeof(nameBuffer)); // Inicializar el buffer a cero
}

// Constructor with parameters. Menu Screen
Menu::Menu(int width, int height, const char* gameTitle, Vector2 initPosition)
    : screenWidth(width), screenHeight(height), windowTitle(gameTitle), windowPosition(initPosition)
{
    Init();
}

// Run the Menu.
void Menu::Run()
{
    while (!exitWindow && !WindowShouldClose())
    {
        Update();
        Draw();
    }
}

// Deinitialize the Menu.
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

    // Actualizar el estado del bot?n
    if (!startbutton && GuiButton(Rectangle{ 580.0f, 400.0f, 100, 40 }, "START GAME")) {
        startbutton = true;
    }

	if (rungamebutton)
    {
		currentstate = GameState::GAME;
    }

    // Create an instance where I clicked the start button.
}

void Menu::DrawBoardMenu()
{
    // Draw the board menu.
    BeginDrawing();
    ClearBackground(RAYWHITE);
    int i;
    int j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
                DrawRectangle(i * 160, j * 160, 160, 160, CLITERAL(Color){188, 200, 187, 255}); // change the color of the board.
            else
                DrawRectangle(i * 160, j * 160, 160, 160, CLITERAL(Color){69, 118, 65, 255}); // change the color of the board. 
        }
    }
}

void Menu::Draw()
{
    BeginDrawing();

    // Change the background because of the button.
    if (startbutton)
    {
        // add logic to change the cpp file to the game one.
        ClearBackground(CLITERAL(Color) { 69, 118, 65, 255 });

        // Draw the player name text box.
        DrawText("Enter your name:", 490, 200, 30, RAYWHITE);
		GuiTextBox(Rectangle{ 455, 240, 340, 30 }, nameBuffer, 25, true); // rectangle { x, y, width, height } GuiTextBox(Rectangle{ x,y, width, height }, buffer, maxchars, editmode)

        if (GuiButton(Rectangle{ 580.0f, 350.0f, 100, 40 }, "READY"))
        {
            player1 = nameBuffer; // Save the player name.
            // Change game status or initialize the game.
			rungamebutton = true;
			exitWindow = true; // this allows me to change the screen to the game one. Exit the menu.
        }
    }
    else
    {
        ClearBackground(RAYWHITE);
        DrawBoardMenu();  // background of the menu. Board menu.

        // Draw the menu.
        GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
		GuiButton(Rectangle{ 580.0f, 400.0f, 100, 40 }, "START GAME"); // rectangle { x, y, width, height }
		DrawText("CHESSY GAME", 390, 200, 70, BLACK); // drawtext ("text", x, y, fontsize, color)
    }

    EndDrawing();
}