#include "King.h"

King::King(bool isWhite, int x, int y) : Piece(isWhite, x, y) {}

wxArrayString King::getPossibleMoves() const {
    wxArrayString moves;
    const int directions[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };
    for (const auto& dir : directions) {
        int newX = posX + dir[0];
        int newY = posY + dir[1];

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            moves.Add(wxString::Format("Move to (%d,%d)", newX, newY));
        }
    }
    return moves;
}
