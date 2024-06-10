#include "Menu.h"
#include "Game.h"

int main()
{
    // Create instance of menu
    Menu menu;
    menu.Run();

    // If the menu ends, the game starts
    if (menu.IsGameStarting()) {
        // Get names
        const char* player1Name = menu.GetPlayer1Name();
        const char* player2Name = menu.GetPlayer2Name();

        menu.Deinit();

        // Start with players names
        Game game(player1Name, player2Name);
        game.Run();
    }

    return 0;
}