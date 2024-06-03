#include "Knight.h"

Knight::Knight(bool isWhite, int x, int y) : Piece(isWhite, x, y) {}

wxArrayString Knight::getPossibleMoves() const {
    wxArrayString moves;
    const int moveOffsets[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    for (const auto& offset : moveOffsets) {
        int newX = posX + offset[0];
        int newY = posY + offset[1];

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            moves.Add(wxString::Format("Move to (%d,%d)", newX, newY));
        }
    }
    return moves;
}
