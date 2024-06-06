#include "Menu.h"
#include "Game.h"


int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    Vector2 initPosition = { 500, 200 };
	Game game(screenWidth, screenHeight, "ChessGame", initPosition);
	game.Run(); // game window.

	// If the game is started, then run the game.
	if (game.currentstate == GameState::GAME) 
    {
		game.RunGame(); // game window.
	}
	
    return 0;
}

