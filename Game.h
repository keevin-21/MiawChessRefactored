#ifndef MEOWCHESS_GAME_H
#define MEOWCHESS_GAME_H

#include "Piece.h"
#include "Board.h"
#include "Moves.h"
#include "raylib.h"

#include <string>
#include <map>

using std::string;

enum GAME_STATE
{
	GS_RUNNING,
	GS_PROMOTION,
	GS_STALEMATE,
	GS_WHITE_WON,
	GS_BLACK_WON
};

class Game
{
public:
	const static int WINDOW_WIDTH = 1280;
	const static int WINDOW_HEIGHT = 720;
	const static int CELL_SIZE = 80;
	const static int INFO_BAR_HEIGHT = 32;

	
	const static Color LIGHT_SHADE;
	const static Color DARK_SHADE;

	const static string TEXTURES_PATH;
	const static string SOUNDS_PATH;
	const static string ASSETS_PATH;

	Game();
	~Game();

	void Run();
	void SwapTurn();

private:
	void LoadTextures();
	void LoadSounds();

	void HandleInput();
	void HandlePromotion();
	void PossibleMoves();
	void DoMoveOnBoard(const Move& move);
	Move* GetMoveFromInput(const Position& position);

	void CheckEndGame();
	void FilterMovesThatAttackKing();
	void FilterMovesThatAvoidCheck();
	bool IsAnyMoveValid();

	// Textures and sounds.
	std::map<string, Texture> textures;
	std::map<string, Sound> sounds;

	// Game state.
	Board board;
	PIECE_COLOR turn = PIECE_COLOR::C_WHITE; // White starts.
	GAME_STATE gameState = GAME_STATE::GS_RUNNING; // Game starts.

	// Selected piece.
	Piece* selectedPiece = nullptr;
	std::map<Piece*, std::vector<Move>> possibleMoves;

	// Game info.
	int round = 1;
	double timer = 0;
};

#endif //MEOWCHESS_GAME_H