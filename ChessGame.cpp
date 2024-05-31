#include "Menu.h"

int main()
{
    Vector2 initPosition = { 500, 200 };
    Menu window(720, 720, "ChessGame", initPosition);
    window.Run();
    return 0;
}