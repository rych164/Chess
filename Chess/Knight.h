#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(bool isWhite, int x, int y);

    wxArrayString getPossibleMoves() const override;
};
