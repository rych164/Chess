#include "Rook.h"

Rook::Rook(bool isWhite, int x, int y) : Piece(isWhite, x, y) {}

wxArrayString Rook::getPossibleMoves() const {
	wxArrayString moves;
	for (int i = 1; i <= 8; i++)
	{
		if (i != posY) {
			moves.Add(wxString::Format("Move to (%d,%d)", posX, i));
		}
		if (i != posX) {
			moves.Add(wxString::Format("MOv to (%d,%d)", i, posY));
		}
	}
	return moves;
}