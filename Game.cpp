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

using std::string;

const string Game::ASSETS_PATH = "assets/";
const string Game::TEXTURES_PATH = ASSETS_PATH + "textures/";
const string Game::SOUNDS_PATH = ASSETS_PATH + "sounds/";

Game::Game()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MeowChess");
	InitAudioDevice();

	SetTargetFPS(60);

	LoadTextures();
	LoadSounds();

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
			HandleInput();
		}

		BeginDrawing();
		{
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
	for(const auto& entry : std::file)
}

void Game::LoadSounds()
{
}

void Game::HandleInput()
{
	if (IsMouseButtonPressed(0)) {
		Vector2 mousePosition = GetMousePosition();
		mousePosition.y -= Game::INFO_BAR_HEIGHT;

		Position clickedPosition = { int(mousePosition.y) / CELL_SIZE, int(mousePosition.x) / CELL_SIZE };
		Piece* clickedPiece = board.At(clickedPosition);

		// Select piece.
		if (clickedPiece != nullptr && clickedPiece->color == turn)
		{
			PlaySound(sounds["click"]);
			selectedPiece = clickedPiece;
		}
		else {
			// Do movement.
			Move* desiredMove = GetMoveFromInput(clickedPosition);

			if (desiredMove && selectedPiece != nullptr)
			{
				DoMoveOnBoard(*desiredMove);
			}
			else
			{
				PlaySound(sounds["clickCancel"]);
			}

			// Piece must still be selected to render promotion screen.
			if (!desiredMove || (desiredMove->type != MOVES::PROMOTION && desiredMove->type != MOVES::ATTACK_PROMOTION))
			{
				selectedPiece = nullptr;
			}
		}
	}
}

void Game::HandlePromotion()
{
	if (IsMouseButtonPressed(0)) {
		Vector2 mousePosition = GetMousePosition();
		mousePosition.y -= Game::INFO_BAR_HEIGHT;

		Position clickedPosition = { int(mousePosition.y) / CELL_SIZE, int(mousePosition.x) / CELL_SIZE };

		if (clickedPosition.i == 3 && clickedPosition.j >= 2 && clickedPosition.j <= 5)
		{
			Piece* newPiece;
			// Clicked queen.
			if (clickedPosition.j == 2)
			{
				newPiece = new Queen(selectedPiece->GetPosition(), selectedPiece->color);
			}
			// Clicked rook.
			else if (clickedPosition.j == 3)
			{ 
				newPiece = new Rook(selectedPiece->GetPosition(), selectedPiece->color);
			}
			// Clicked bishop.
			else if (clickedPosition.j == 4)
			{
				newPiece = new Bishop(selectedPiece->GetPosition(), selectedPiece->color);
			}
			// Clicked knight.
			else
			{
				newPiece = new Knight(selectedPiece->GetPosition(), selectedPiece->color);
			}

			// Destroy peon, create new piece at same position.
			board.Destroy(selectedPiece->GetPosition());
			board.Add(newPiece);

			// Quit promotion, deselect peon and swap turns.
			gameState = GAME_STATE::GS_RUNNING;

			selectedPiece = nullptr;
			possibleMoves.clear();

			SwapTurn();
		}
	}
}

void Game::PossibleMoves()
{
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
	for (auto& [piece, moves] : possibleMoves)
	{
		if (piece == selectedPiece)
		{
			for (Move& move : moves)
			{
				if (move.position.i == position.i && move.position.j == position.j)
				{
					return &move;
				}
			}
		}
	}
}

void Game::CheckEndGame()
{
}

void Game::FilterMovesThatAttackKing()
{
}

void Game::FilterMovesThatAvoidCheck()
{
}

bool Game::IsAnyMoveValid()
{
	return false;
}
