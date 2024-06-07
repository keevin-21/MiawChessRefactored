#include "Board.h"
#include "raylib.h"
#include <vector>

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Chess Game");

    Board board;

    SetTargetFPS(60);

    Vector2 selectedPos = { -1, -1 };  // position of the selected piece
    std::vector<Vector2> possibleMoves;
    std::vector<Vector2> captureMoves;

    while (!WindowShouldClose())
    {
        // move a piece
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
            Vector2 clickedPos = { floor(mousePosition.x / 80), floor(mousePosition.y / 80) };

            if (selectedPos.x == -1 && selectedPos.y == -1) {
                // select a piece
                Piece* selectedPiece = board.GetPieceAtPosition(clickedPos);
                if (selectedPiece) {
                    selectedPos = clickedPos;
                    possibleMoves = selectedPiece->GetPossibleMoves(); // Get possible moves
                    captureMoves = selectedPiece->GetCaptureMoves(); // Get capture moves
                }
            }
            else {
                // try to move the selected piece
                Piece* selectedPiece = board.GetPieceAtPosition(selectedPos);
                if (selectedPiece) {
                    if (selectedPiece->CanMove(clickedPos)) {
                        selectedPiece->Move(clickedPos);
                    }
                    else if (selectedPiece->IsCaptureMove(clickedPos, board)) {
                        selectedPiece->Move(clickedPos);
                    }
                    selectedPos = { -1, -1 }; // unselect the piece after moving
                    possibleMoves.clear(); // Clear possible moves after moving
                    captureMoves.clear(); // Clear capture moves after moving
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        board.Draw();

        // Draw possible moves
        for (const Vector2& move : possibleMoves) {
            DrawCircleV({ move.x * 80 + 40, move.y * 80 + 40 }, 20, Fade(GREEN, 0.5f));
        }

        // Draw capture moves
        for (const Vector2& move : captureMoves) {
            DrawCircleV({ move.x * 80 + 40, move.y * 80 + 40 }, 20, Fade(RED, 0.5f));
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
