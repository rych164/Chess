#include "Pawn.h"

Pawn::Pawn(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>* board)
    : Piece(isWhite, x, y)
{
    setBoard(board);
}

wxArrayString Pawn::getPossibleMoves() const {
    wxArrayString moves;
    int direction = isWhite() ? 1 : -1;  // Determines movement direction based on color
    int startRow = isWhite() ? 1 : 6;    // Determines the starting row for a double move

    int forwardX = posX + direction;
    // Check the forward move
    if (forwardX >= 0 && forwardX < 8 && !(*board)[forwardX][posY]) {
        moves.Add(wxString::Format("Move to (%d, %d)", forwardX, posY));
    }

    // Check the double step forward on the first move
    if (posX == startRow && !(*board)[forwardX][posY] && forwardX + direction >= 0 && forwardX + direction < 8 && !(*board)[forwardX + direction][posY]) {
        moves.Add(wxString::Format("Move to (%d, %d)", forwardX + direction, posY));
    }

    // Capture moves
    for (int dy : {-1, 1}) {
        int newY = posY + dy;
        if (forwardX >= 0 && forwardX < 8 && newY >= 0 && newY < 8 && (*board)[forwardX][newY] && (*board)[forwardX][newY]->isWhite() != isWhite()) {
            moves.Add(wxString::Format("Capture at (%d, %d)", forwardX, newY));
        }
    }

    return moves;
}
