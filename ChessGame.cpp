#include "Menu.h"
#include "Board.h"
#include "raylib.h"
    

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
  
    Vector2 initPosition = { 500, 200 };
    Menu window(screenWidth, screenHeight, "ChessGame", initPosition);
    window.Run();

    Board board;

    SetTargetFPS(60);

    Vector2 selectedPos = { -1, -1 };  // position of the selected piece

    while (!WindowShouldClose())
    {
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

        BeginDrawing();
        ClearBackground(RAYWHITE);

        board.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
