#include "Queen.h"

Queen::Queen(bool isWhite, int x, int y) : Piece(isWhite, x, y) {}

wxArrayString Queen::getPossibleMoves() const {
	wxArrayString moves;

	const int directions[8][2] = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
	};

	for (auto& dir : directions)
	{
		int x = posX;
		int y = posY;
		while (true) {
			x += dir[0];
			y += dir[1];
			if (x < 0 || x >= 8 || y < 0 || y >= 8)
			{
				break;
			}
		}
		moves.Add(wxString::Format("Move to {%d,%d}", x, y));
	}
	return moves;
}