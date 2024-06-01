#include "Knight.h"

Knight::Knight(bool isWhite, int x, int y) : Piece(isWhite, x, y){}

wxArrayString Knight::getPossibleMoves() const {
	wxArrayString moves;
	const int moveOffSets[8][2] = {
		{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
	};

	for (int i = 0; i < 8; i++)
	{
		int newX = posX + moveOffSets[i][0];
		int newY = posY + moveOffSets[i][1];

		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
		{
			moves.Add(wxString::Format("Move to (%d,%d)", newX, newY));
		}
	}
	return moves;
}