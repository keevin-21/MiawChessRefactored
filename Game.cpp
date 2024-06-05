#include "Game.h"

Game::Game(int screenWidth, int screenHeight, const char* GameTitle, Vector2 initPosition)
    : Menu(screenWidth, screenHeight, GameTitle, initPosition), board(), selectedPos({ -1, -1 })
{
    currentstate = GameState::GAME;
}

Game::~Game()
{
    // close window
    CloseWindow();
}

void Game::RunGame()
{
    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }
}

void Game::DrawGame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    board.Draw();

    EndDrawing();
}

void Game::UpdateGame()
{
    // Controls of the game, keys.
    // move a piece
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        Vector2 clickedPos = { floor(mousePosition.x / 80), floor(mousePosition.y / 80) };

        if (selectedPos.x == -1 && selectedPos.y == -1) {
            // selecy a piece
            Piece* selectedPiece = board.GetPieceAtPosition(clickedPos);
            if (selectedPiece) {
                selectedPos = clickedPos;
            }
        }
        else {
            // try to move the selected piece
            Piece* selectedPiece = board.GetPieceAtPosition(selectedPos);
            if (selectedPiece) {
                if (selectedPiece->IsWhite()) {
                    Vector2 targetPos = { selectedPos.x, selectedPos.y - 1 }; // movement test for white
                    if (selectedPiece->CanMove(targetPos)) {
                        selectedPiece->Move(targetPos);
                    }
                }
                else {
                    Vector2 targetPos = { selectedPos.x, selectedPos.y + 1 }; // movement test for black
                    if (selectedPiece->CanMove(targetPos)) {
                        selectedPiece->Move(targetPos);
                    }
                }
                selectedPos = { -1, -1 }; // unselect the piece after moving
            }
        }
    }
}