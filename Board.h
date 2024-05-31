#include "Piece.h"
#include <vector>

using std::vector;

class Board
{
private:
	vector<Piece*> pieces;

public:
	Board();
	~Board();

	void Draw();
	void InitializePieces();
	
	Piece* GetPieceAtPosition(Vector2 pos);
};
