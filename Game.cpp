#include "Game.h"
#include "Renderer.h"
#include "raylib.h"
#include "Position.h"
#include "Queen.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using std::string;

const string Game::ASSETS_PATH = "assets/";
const string Game::TEXTURES_PATH = ASSETS_PATH + "textures/";
const string Game::SOUNDS_PATH = ASSETS_PATH + "sounds/";
const string Game::FONTS_PATH = ASSETS_PATH + "fonts/";

const Color Game::LIGHT_SHADE = Color{ 255, 217, 237, 255 };
const Color Game::DARK_SHADE = Color{ 255, 104, 182, 255 };

Game::Game(const std::string& p1Name, const std::string& p2Name)
	: player1Name(p1Name), player2Name(p2Name) 
{
	// InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MeowChess");
	InitAudioDevice();

	SetTargetFPS(60);

	LoadTextures();
	LoadSounds();
	LoadFonts();

	board.Init();
	PossibleMoves();
}

Game::~Game()
{
	for(auto const& texture : textures)
	{
		UnloadTexture(texture.second);
	}

	for(auto const& sound : sounds)
	{
		UnloadSound(sound.second);
	}

	for (auto const& font : fonts)
	{
		UnloadFont(font.second); 
	}

	board.Clear();

	CloseAudioDevice();
	CloseWindow();
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		if(gameState == GAME_STATE::GS_RUNNING)
		{
			HandleInput();
			timer += GetFrameTime();
		}

		if(gameState == GAME_STATE::GS_PROMOTION)
		{
			HandlePromotion();
		}

		BeginDrawing();
		{
			DrawTexture(textures["MEAW_GAME"], 0, 0, WHITE);
			Font font = fonts["FONT1"]; 
			DrawTextEx(font, player1Name.c_str(), Vector2{ 110, 325 }, 30, 2, BLACK); 
			DrawTextEx(font, player2Name.c_str(), Vector2{ 1100, 350 }, 30, 2, BLACK);

			std::vector<Move> moveSelectedPiece;

			if (selectedPiece)
			{
				moveSelectedPiece = possibleMoves.at(selectedPiece);
			}

			// Renderer.
			Renderer::MouseCursor(board, moveSelectedPiece, turn, gameState == GAME_STATE::GS_PROMOTION);
			Renderer::Clear();
			Renderer::RenderBackground();
			Renderer::RenderPieces(board, textures);

			if (gameState != GAME_STATE::GS_PROMOTION)
			{
				Renderer::RenderPossibleMoves(textures, moveSelectedPiece);
			}

			Renderer::RenderGuide();
			Renderer::RenderInfo(round, timer);

			if (gameState == GAME_STATE::GS_PROMOTION)
			{
				Renderer::RenderPromotion(textures, selectedPiece->color);
			}

			// Render end-game screen.
			if (gameState == GAME_STATE::GS_WHITE_WON || gameState == GAME_STATE::GS_BLACK_WON)
			{
				Renderer::RenderEndGame(gameState);
			}
		}
		EndDrawing();
	}
}

void Game::SwapTurn()
{
	turn = Piece::GetInverseColor(turn);

	// Advance round.
	if (turn == PIECE_COLOR::C_WHITE)
	{
		round++;
	}

	// Calculate all possible movements for the current pieces.
	PossibleMoves();

	// Check for stalemates or checkmates. If so, ends the game.
	CheckEndGame();
}

void Game::LoadTextures()
{
	for (const auto& entry : std::filesystem::directory_iterator(TEXTURES_PATH))
	{
		// Load and resize image.
		Image image = LoadImage(entry.path().string().c_str());
		ImageResize(&image, CELL_SIZE, CELL_SIZE);

		Texture texture = LoadTextureFromImage(image);

		// Add texture to map.
		string textureName = entry.path().filename().string();
		size_t dotIndex = textureName.find('.');

		string fileNameNoExtension = entry.path().filename().string().substr(0, dotIndex);
		textures[fileNameNoExtension] = texture;

		UnloadImage(image);
	}

	// Load Backgrounds
	textures["MEAW_GAME"] = LoadTexture((TEXTURES_PATH + "MEAW_GAME.png").c_str());
}

void Game::LoadSounds()
{
	for (const auto& entry : std::filesystem::directory_iterator(SOUNDS_PATH))
	{
		// Load sound.
		Sound sound = LoadSound(entry.path().string().c_str());

		// Add sound to map of sounds.
		std::string fileName = entry.path().filename().string();
		size_t dotIndex = fileName.find('.');

		std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
		sounds[fileNameWithoutExtension] = sound;
	}
}

void Game::LoadFonts()
{
	// Load Fonts
	fonts["FONT1"] = LoadFont((FONTS_PATH + "Espressonal.otf").c_str()); 
	fonts["FONT2"] = LoadFont((FONTS_PATH + "Sono-Bold.ttf").c_str()); 
	fonts["FONT3"] = LoadFont((FONTS_PATH + "CoffeeFills.ttf").c_str()); 
	fonts["FONT4"] = LoadFont((FONTS_PATH + "SuperCreamy.ttf").c_str()); 
}

void Game::HandleInput()
{
	if (IsMouseButtonPressed(0)) {
		Vector2 mousePosition = GetMousePosition();

		// Ajuste de la posición del ratón tomando en cuenta el offset del tablero
		int offsetX = (Game::WINDOW_WIDTH - 8 * Game::CELL_SIZE) / 2;
		int offsetY = (Game::WINDOW_HEIGHT - Game::INFO_BAR_HEIGHT - 8 * Game::CELL_SIZE) / 2 + Game::INFO_BAR_HEIGHT;

		mousePosition.x -= offsetX;
		mousePosition.y -= offsetY;

		// Verificación de que el clic esté dentro de los límites del tablero
		if (mousePosition.x >= 0 && mousePosition.y >= 0 &&
			mousePosition.x < 8 * Game::CELL_SIZE && mousePosition.y < 8 * Game::CELL_SIZE) {

			Position clickedPosition = { int(mousePosition.y) / CELL_SIZE, int(mousePosition.x) / CELL_SIZE };
			Piece* clickedPiece = board.At(clickedPosition);

			// Selección de la pieza
			if (clickedPiece != nullptr && clickedPiece->color == turn)
			{
				PlaySound(sounds["click"]);
				selectedPiece = clickedPiece;
			}
			else {
				// Movimiento de la pieza
				Move* desiredMove = GetMoveFromInput(clickedPosition);

				if (desiredMove && selectedPiece != nullptr)
				{
					DoMoveOnBoard(*desiredMove);
				}
				else
				{
					PlaySound(sounds["clickCancel"]);
				}

				// La pieza debe seguir seleccionada para mostrar la pantalla de promoción
				if (!desiredMove || (desiredMove->type != MOVES::PROMOTION && desiredMove->type != MOVES::ATTACK_PROMOTION))
				{
					selectedPiece = nullptr;
				}
			}
		}
	}
}


void Game::HandlePromotion()
{
	if (IsMouseButtonPressed(0)) {
		Vector2 mousePosition = GetMousePosition();
		mousePosition.y -= Game::INFO_BAR_HEIGHT;

		int offsetX = (Game::WINDOW_WIDTH - 8 * Game::CELL_SIZE) / 2;
		int offsetY = (Game::WINDOW_HEIGHT - Game::INFO_BAR_HEIGHT - 8 * Game::CELL_SIZE) / 2 + Game::INFO_BAR_HEIGHT;

		mousePosition.x -= offsetX;
		mousePosition.y -= offsetY;

		Position clickedPosition = { static_cast<int>(mousePosition.y) / CELL_SIZE, static_cast<int>(mousePosition.x) / CELL_SIZE };

		if (clickedPosition.i == 3 && clickedPosition.j >= 2 && clickedPosition.j <= 5)
		{
			Piece* newPiece = nullptr;

			if (clickedPosition.j == 2)
			{
				newPiece = new Queen(selectedPiece->GetPosition(), selectedPiece->color);
			}
			else if (clickedPosition.j == 3)
			{
				newPiece = new Rook(selectedPiece->GetPosition(), selectedPiece->color);
			}
			else if (clickedPosition.j == 4)
			{
				newPiece = new Bishop(selectedPiece->GetPosition(), selectedPiece->color);
			}
			else if (clickedPosition.j == 5)
			{
				newPiece = new Knight(selectedPiece->GetPosition(), selectedPiece->color);
			}

			if (newPiece)
			{
				board.Destroy(selectedPiece->GetPosition());
				board.Add(newPiece);

				gameState = GAME_STATE::GS_RUNNING;
				selectedPiece = nullptr;
				possibleMoves.clear();

				SwapTurn();
			}
		}
	}
}



void Game::PossibleMoves()
{
	possibleMoves.clear();

	for (Piece* piece : board.GetPiecesByColor(turn))
	{
		possibleMoves[piece] = piece->GetPossibleMoves(board);
	}

	// Remove the moves that could destroy the king.
	FilterMovesThatAttackKing();

	// Remove the moves that could lead to a check.
	FilterMovesThatAvoidCheck();
}

void Game::DoMoveOnBoard(const Move& move)
{
	board.DoMove(selectedPiece, move);

	// If the move was a promotion move, show the promotion screen. Else, swap turns.
	if (move.type == MOVES::PROMOTION || move.type == MOVES::ATTACK_PROMOTION)
	{
		gameState = GAME_STATE::GS_PROMOTION;
	}
	else
	{
		SwapTurn();
	}
}

Move* Game::GetMoveFromInput(const Position& position)
{
	for (auto& entry : possibleMoves)
	{
		auto& piece = entry.first;
		auto& moves = entry.second;

		if (piece == selectedPiece)
		{
			for (Move& move : moves)
			{
				if (move.position.i == position.i && move.position.j == position.j)
				{
					return &move; // Return a pointer to the found move
				}
			}
		}
	}
	return nullptr; // Return nullptr if no valid move is found
}

void Game::CheckEndGame()
{
	std::vector<Piece*> piecesOfCurrentTurn = board.GetPiecesByColor(turn);

	if (board.IsInCheck(turn))
	{
		// If there are no moves possible and in check, declare checkmate.
		if (!IsAnyMoveValid())
		{
			gameState = (turn == PIECE_COLOR::C_WHITE ? GAME_STATE::GS_BLACK_WON : GAME_STATE::GS_WHITE_WON);
		}
	}
	else if (!IsAnyMoveValid())
	{
		// If not in check and there is not any move possible, declare stalemate.
		gameState = GAME_STATE::GS_STALEMATE;
	}
}

void Game::FilterMovesThatAttackKing()
{
	for (auto& [piece, possibleMoves] : possibleMoves)
	{
		for (int i = possibleMoves.size() - 1; i >= 0; i--)
		{
			Move& move = possibleMoves[i];

			// Remove moves that attack the opponent's king.
			bool isAttackMove = move.type == MOVES::ATTACK || move.type == MOVES::ATTACK_PROMOTION;

			if (isAttackMove)
			{
				Piece* attackedPiece = board.At(move.position);

				if (attackedPiece->type == PIECE_TYPE::KING && attackedPiece->color != turn)
				{
					possibleMoves.erase(possibleMoves.begin() + i);
				}
			}
		}
	}
}

void Game::FilterMovesThatAvoidCheck()
{
	for (auto& [piece, possibleMoves] : possibleMoves) {
		for (int i = possibleMoves.size() - 1; i >= 0; i--) {
			Move& move = possibleMoves[i];

			// If short castling or long castling, check for intermediary positions between king and rook.
			if (move.type == MOVES::SHORT_CASTLE || move.type == MOVES::LONG_CASTLE) {
				std::vector<Position> intermediaryPositions;

				if (move.type == MOVES::SHORT_CASTLE) {
					intermediaryPositions = { {piece->GetPosition().i, 5}, {piece->GetPosition().i, 6} };
				}
				else {
					intermediaryPositions = { {piece->GetPosition().i, 3}, {piece->GetPosition().i, 2} };
				}

				for (const Position& position : intermediaryPositions) {
					if (board.MoveLeadsToCheck(piece, { MOVES::STEP, position })) {
						possibleMoves.erase(possibleMoves.begin() + i);
						break;
					}
				}

				// If normal move.
			}
			else if (board.MoveLeadsToCheck(piece, possibleMoves[i])) {
				possibleMoves.erase(possibleMoves.begin() + i);
			}
		}
	}
}

bool Game::IsAnyMoveValid()
{
	for (const auto& [pieceName, possibleMoves] : possibleMoves)
	{
		if (!possibleMoves.empty())
		{
			return true;
		}
	}
	return false;
}
