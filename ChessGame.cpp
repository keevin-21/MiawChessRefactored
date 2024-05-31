#include "Board.h"
#include "raylib.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Chess Game");

    Board board;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // move a piece
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
            Vector2 selectedPos = { floor(mousePosition.x / 80), floor(mousePosition.y / 80) };

            Piece* selectedPiece = board.GetPieceAtPosition(selectedPos);

            // white pieces move up
            if (selectedPiece && selectedPiece->IsWhite())
            {
                Vector2 targetPos = { selectedPos.x, selectedPos.y - 1 }; // movement test
                if (selectedPiece->CanMove(targetPos))
                {
                    selectedPiece->Move(targetPos);
                }
            }

            // black pieces move down
            if (selectedPiece && selectedPiece->IsWhite() == false)
            {
                Vector2 targetPos = { selectedPos.x, selectedPos.y + 1 }; // movement test
                if (selectedPiece->CanMove(targetPos))
                {
                    selectedPiece->Move(targetPos);
                }
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            board.Draw();

            EndDrawing();
        }

        CloseWindow();
        return 0;
    }
}
