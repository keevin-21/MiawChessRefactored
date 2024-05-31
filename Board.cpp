#include "Board.h"
#include "raylib.h"
#include <iostream>

Board::Board() {
    InitializePieces();
}

Board::~Board() {
    for (auto piece : pieces) {
        delete piece;
    }
}

void Board::Draw() {
    // drawing the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0)
                DrawRectangle(i * 80, j * 80, 80, 80, WHITE);
            else
                DrawRectangle(i * 80, j * 80, 80, 80, DARKGRAY);
        }
    }

    // drawing the pieces
    for (auto piece : pieces) {
        piece->Draw();
    }

}

void Board::InitializePieces() {
    // initialize pawns
    for (int i = 0; i < 8; i++) {
        pieces.push_back(new Pawn({ (float)i, 6 }, true));
        pieces.push_back(new Pawn({ (float)i, 1 }, false));
    }
}

Piece* Board::GetPieceAtPosition(Vector2 pos) {
    for (auto piece : pieces) {
        if (piece->GetPosition().x == pos.x && piece->GetPosition().y == pos.y) {
            return piece;
        }
    }
    return nullptr;
}
