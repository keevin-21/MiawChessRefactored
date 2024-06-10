#define RAYGUI_IMPLEMENTATION
#include "Menu.h"
#include <filesystem>

namespace fs = std::filesystem;
using std::string;

using std::cout;
using std::endl;

const string Menu::ASSETS_PATH = "assets/";
const string Menu::TEXTURES_PATH = ASSETS_PATH + "textures/";
const string Menu::SOUNDS_PATH = ASSETS_PATH + "sounds/";
const string Menu::FONTS_PATH = ASSETS_PATH + "fonts/"; 

Menu::Menu() : currentState(MS_START), dragWindow(false), exitWindow(false)
{
	SetTargetFPS(60);

	// Initialize player names with empty strings
	player1Name[0] = '\0';
	player2Name[0] = '\0';
}

Menu::~Menu()
{
	for (auto const& texture : textures)
	{
		UnloadTexture(texture.second);
	}

	for (auto const& sound : sounds)
	{
		UnloadSound(sound.second); 
	}
	for (auto const& font : fonts)
	{
		UnloadFont(font.second); 
	}
}

void Menu::Deinit()
{
	CloseAudioDevice();
	CloseWindow();
}

void Menu::Run()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MeowChess");
	InitAudioDevice();

	LoadTextures();
	LoadSounds();
	LoadFonts();

	while (!exitWindow && !WindowShouldClose())
	{
		Update();
		Draw();
	}

	Deinit();
}

void Menu::LoadTextures()
{
	// Load Backgrounds
	textures["MEAW_START"] = LoadTexture((TEXTURES_PATH + "MEAW_START.png").c_str());
	textures["MEAW_NAME"] = LoadTexture((TEXTURES_PATH + "MEAW_NAME.png").c_str());

	// Load Buttons
	textures["MEAW_PLAY"] = LoadTexture((TEXTURES_PATH + "MEAW_PLAY.png").c_str());
	textures["MEAW_SAVE1"] = LoadTexture((TEXTURES_PATH + "MEAW_SAVE1.png").c_str());
	textures["MEAW_SAVE2"] = LoadTexture((TEXTURES_PATH + "MEAW_SAVE2.png").c_str());
	textures["MEAW_NEXT"] = LoadTexture((TEXTURES_PATH + "MEAW_NEXT.png").c_str());
}

void Menu::LoadSounds()
{
	// Nothing for now
	// sounds["example_sound"] = LoadSound((SOUNDS_PATH + "example_sound.wav").c_str());
}

void Menu::LoadFonts()
{
	// Load Fonts
	fonts["FONT1"] = LoadFont((FONTS_PATH + "Espressonal.otf").c_str());
	fonts["FONT2"] = LoadFont((FONTS_PATH + "Sono-Bold.ttf").c_str());
	fonts["FONT3"] = LoadFont((FONTS_PATH + "CoffeeFills.ttf").c_str());
	fonts["FONT4"] = LoadFont((FONTS_PATH + "SuperCreamy.ttf").c_str());
}

void Menu::Update()
{
	switch (currentState)
	{
	case MS_START:
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
		{
			Vector2 mousePos = GetMousePosition(); 
			// Get the dimensions of the MEAW_PLAY texture
			int playButtonWidth = textures["MEAW_PLAY"].width;  
			int playButtonHeight = textures["MEAW_PLAY"].height; 

			// Check if the "Play" button is clicked
			if (mousePos.x > 580 && mousePos.x < 580 + playButtonWidth && 
				mousePos.y > 585 && mousePos.y < 585 + playButtonHeight) 
			{
				cout << "----------- PLAY -----------" << endl;
				currentState = MS_NAMES; 
			}
		}
		break;

	case MS_NAMES:
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			Vector2 mousePos = GetMousePosition();
			// Get the dimensions of the MEAW_SAVE1 texture
			int save1ButtonWidth = textures["MEAW_SAVE1"].width;
			int save1ButtonHeight = textures["MEAW_SAVE1"].height;
			// Get the dimensions of the MEAW_SAVE2 texture
			int save2ButtonWidth = textures["MEAW_SAVE2"].width;
			int save2ButtonHeight = textures["MEAW_SAVE2"].height;
			// Get the dimensions of the MEAW_NEXT texture
			int nextButtonWidth = textures["MEAW_NEXT"].width;
			int nextButtonHeight = textures["MEAW_NEXT"].height;

			if (CheckCollisionPointRec(mousePos, { 240, 305, 250, 50 }))
			{
				currentInputPlayer = 1;
			}
			if (CheckCollisionPointRec(mousePos, { 730, 305, 250, 50 }))
			{
				currentInputPlayer = 2; 
			}

			// Check if the "Save 1" button is clicked
			if (mousePos.x > 540 && mousePos.x < 540 + save1ButtonWidth &&
				mousePos.y > 305 && mousePos.y < 305 + save1ButtonHeight)
			{
				// Save the name entered in player1Name
				cout << "----------- SAVE 1 -----------" << endl;
				strncpy(player1Name, GetPlayer1Name(), sizeof(player1Name) - 1);
				player1Name[sizeof(player1Name) - 1] = '\0'; // Asegúrate de que el string termina con '\0'  
				cout << "Nombre del jugador 1 guardado: " << player1Name << endl;
				currentInputPlayer = 1;
			}

			// Check if the "Save 2" button is clicked
			if (mousePos.x > 1030 && mousePos.x < 1030 + save2ButtonWidth &&
				mousePos.y > 305 && mousePos.y < 305 + save2ButtonHeight)
			{
				// Save the name entered in player2Name
				cout << "----------- SAVE 2 -----------" << endl;
				strncpy(player2Name, GetPlayer2Name(), sizeof(player2Name) - 1); 
				player2Name[sizeof(player2Name) - 1] = '\0'; // Asegúrate de que el string termina con '\0'  
				cout << "Nombre del jugador 2 guardado: " << player2Name << endl;  
				currentInputPlayer = 2; 
			}

			// Check if the "Next" button is clicked
			if (mousePos.x > 1200 && mousePos.x < 1200 + nextButtonWidth &&
				mousePos.y > 40 && mousePos.y < 40 + nextButtonHeight)
			{
				cout << "----------- NEXT -----------" << endl;
				currentState = MS_GAME;
			}
		}

		// MANAGE KEYBOARD
		if (IsKeyPressed(KEY_BACKSPACE))
		{
			if (currentInputPlayer == 1 && strlen(player1Name) > 0)
			{
				player1Name[strlen(player1Name) - 1] = '\0';
			}
			else if (currentInputPlayer == 2 && strlen(player2Name) > 0)
			{
				player2Name[strlen(player2Name) - 1] = '\0';
			}
		}
		else
		{
			int key = GetKeyPressed();
			if (key >= 32 && key <= 126)
			{
				if (currentInputPlayer == 1 && strlen(player1Name) < 31)
				{
					player1Name[strlen(player1Name)] = (char)key;
					player1Name[strlen(player1Name) + 1] = '\0';
				}
				else if (currentInputPlayer == 2 && strlen(player2Name) < 31)
				{
					player2Name[strlen(player2Name)] = (char)key;
					player2Name[strlen(player2Name) + 1] = '\0';
				}
			}
		}
		break;

	case MS_GAME:
		// Transition to game logic, handled outside of Menu class
		exitWindow = true;
		break;
	}
}

void Menu::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	switch (currentState)
	{
	case MS_START:
		DrawStartScreen();
		break;

	case MS_NAMES:
		DrawNamesScreen();
		break;

	case MS_GAME:
		// Logic handled outside of Menu class
		break;
	}

	EndDrawing();
}

bool Menu::IsGameStarting() const
{
	return currentState == MS_GAME;
}

void Menu::DrawStartScreen()
{
	// Background
	DrawTexture(textures["MEAW_START"], 0, 0, WHITE); 
	// Play Button
	Vector2 PlayPosition = { 580, 585 };
	DrawTextureEx(textures["MEAW_PLAY"], PlayPosition, 0.0f, 1.0f, WHITE);
}

void Menu::DrawNamesScreen()
{
	// Background
	DrawTexture(textures["MEAW_NAME"], 0, 0, WHITE);

	// Fonts
	// Font font1 = fonts["FONT1"];
	// Font font2 = fonts["FONT2"];
	Font font3 = fonts["FONT3"];

	// PLAYER 1
	Vector2 Save1Position = { 540, 305 }; 
	DrawTextureEx(textures["MEAW_SAVE1"], Save1Position, 0.0f, 1.0f, WHITE); 
	DrawRectangleRounded(Rectangle{ 240, 307, 280, 55 }, 5.0f, 5.0f, WHITE);  
	DrawTextEx(font3, player1Name, Vector2{ 260, 325 }, 20, 2, BLACK);  

	// PLAYER 2
	Vector2 Save2Position = { 1030, 305 }; 
	DrawTextureEx(textures["MEAW_SAVE2"], Save2Position, 0.0f, 1.0f, WHITE); 
	DrawRectangleRounded(Rectangle{ 730, 307, 280, 55 }, 5.0f, 5.0f, WHITE);  
	DrawTextEx(font3, player2Name, Vector2{ 750, 325 }, 20, 2, BLACK);  

	// Next Button
	Vector2 NextPosition = { 1200, 40 }; 
	DrawTextureEx(textures["MEAW_NEXT"], NextPosition, 0.0f, 1.0f, WHITE); 
}