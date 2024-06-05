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

    // Actualizar el estado del botón
    if (!startbutton && GuiButton(Rectangle{ 305.0f, 400.0f, 100, 40 }, "START GAME")) {
        startbutton = true;
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
				DrawRectangle(i * 90, j * 90, 90, 90, LIME); // change the color of the board.
            else
                DrawRectangle(i * 90, j * 90, 90, 90, DARKGREEN);
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
        ClearBackground(BLACK);
        exitWindow = GuiWindowBox(Rectangle{ 0.0f, 0.0f, static_cast<float>(screenWidth), 20.0f }, "#198# CHESSY GAME");

		// Draw the player name text box.
        DrawText("Enter your name:", 190, 200, 20, RAYWHITE);
        GuiTextBox(Rectangle{ 190, 240, 340, 30 }, nameBuffer, 20, true);

        if (GuiButton(Rectangle{ 305.0f, 300.0f, 100, 40 }, "READY")) 
        {
			player1 = nameBuffer; // Save the player name.
            // Change game status or initialize the game.
			startbutton = false; // return to the menu. But here is the game.
        }
    }
    else 
    {
        ClearBackground(RAYWHITE);
		DrawBoardMenu();  // background of the menu. Board menu.

		// Draw the menu.
        // exitWindow = GuiWindowBox(Rectangle{ 0.0f, 0.0f, static_cast<float>(screenWidth), 20.0f }, "#198# CHESSY GAME");
        GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiButton(Rectangle{ 305.0f, 400.0f, 100, 40 }, "START GAME");
        DrawText("CHESSY GAME", 190, 200, 50, BLACK);
    }

    EndDrawing();
}