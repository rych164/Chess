#pragma once

#include "Piece.h"

class King : public Piece
{
public:
    King(bool isWhite, int x, int y);

    wxArrayString getPossibleMoves() const override;
};
