#include "Pawn.h"

Pawn::Pawn(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>* boardRef)
    : Piece(isWhite, x, y), board(boardRef) {}

wxArrayString Pawn::getPossibleMoves() const {
    wxArrayString moves;
    int direction = isWhite() ? -1 : 1;  // Determines movement direction based on color
    int startRow = isWhite() ? 6 : 1;    // Determines the starting row for a double move

    int forwardX = posX + direction;
    wxLogDebug("Pawn position: (%d, %d)", posX, posY);
    wxLogDebug("Direction: %d, Start Row: %d", direction, startRow);

    // Check the forward move
    if (forwardX >= 0 && forwardX < 8 && !(*board)[forwardX][posY]) {
        wxString move = wxString::Format("Move to (%d,%d)", forwardX, posY);
        moves.Add(move);
        wxLogDebug("Pawn forward move: %s", move);
    }
    else {
        wxLogDebug("Forward move blocked at (%d, %d)", forwardX, posY);
    }

    // Check the double step forward on the first move
    if (posX == startRow && !(*board)[forwardX][posY] && forwardX + direction >= 0 && forwardX + direction < 8 && !(*board)[forwardX + direction][posY]) {
        wxString move = wxString::Format("Move to (%d,%d)", forwardX + direction, posY);
        moves.Add(move);
        wxLogDebug("Pawn double step move: %s", move);
    }
    else {
        wxLogDebug("Double step move blocked at (%d, %d)", forwardX + direction, posY);
    }

    // Capture moves
    for (int dy : {-1, 1}) {
        int newY = posY + dy;
        if (forwardX >= 0 && forwardX < 8 && newY >= 0 && newY < 8) {
            if ((*board)[forwardX][newY] && (*board)[forwardX][newY]->isWhite() != isWhite()) {
                wxString move = wxString::Format("Capture at (%d,%d)", forwardX, newY);
                moves.Add(move);
                wxLogDebug("Pawn capture move: %s", move);
            }
            else {
                wxLogDebug("No capture possible at (%d, %d)", forwardX, newY);
            }
        }
        else {
            wxLogDebug("Capture move out of bounds at (%d, %d)", forwardX, newY);
        }
    }

    return moves;
}
