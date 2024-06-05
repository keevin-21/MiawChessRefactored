#pragma once
#include "raylib.h"

class Piece
{
protected:
    Vector2 position;
    bool isWhite;

public:
    Piece(Vector2 pos, bool white) : position(pos), isWhite(white) {}
    virtual ~Piece() {}

    virtual void Draw() = 0;
    virtual bool CanMove(Vector2 newPos) = 0;
    virtual void Move(Vector2 newPos) = 0;

    Vector2 GetPosition() const { return position; }
    bool IsWhite() const { return isWhite; }
};

class Pawn : public Piece
{
public:
    Pawn(Vector2 pos, bool white) : Piece(pos, white) {}

    void Draw() override
    {
        DrawCircleV({ position.x * 80 + 40, position.y * 80 + 40 }, 30, isWhite ? WHITE : BLACK);
    }

    bool CanMove(Vector2 newPos) override
    {
        int direction = isWhite ? -1 : 1;

        // moves 1 square forward
        if (newPos.x == position.x && newPos.y == position.y + direction)
        {
            return true;
        }

        // moves 2 squares forward if it's the first move
        if (newPos.x == position.x && newPos.y == position.y + 2 * direction &&
            ((isWhite && position.y == 6) || (!isWhite && position.y == 1)))
        {
            return true;
        }

        // diagonal capture
        if ((newPos.x == position.x + 1 || newPos.x == position.x - 1) &&
            newPos.y == position.y + direction)
        {
            return true;
        }

        return false;
    }

    void Move(Vector2 newPos) override
    {
        if (CanMove(newPos))
        {
            position = newPos;
        }
    }
};
