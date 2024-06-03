#include "Bishop.h"

Bishop::Bishop(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>* board)
    : Piece(isWhite, x, y)
{
    setBoard(board);
}

wxArrayString Bishop::getPossibleMoves() const {
    wxArrayString moves;
    const int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    for (const auto& dir : directions) {
        int x = posX;
        int y = posY;
        while (true) {
            x += dir[0];
            y += dir[1];
            if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                break;
            }
            moves.Add(wxString::Format("Move to (%d,%d)", x, y));
            // Check for an obstacle (another piece)
            if ((*board)[x][y]) {
                break; // Stop if another piece is encountered
            }
        }
    }
    return moves;
}
