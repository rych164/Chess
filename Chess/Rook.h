#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(bool isWhite, int x, int y);

    wxArrayString getPossibleMoves() const override;
};
