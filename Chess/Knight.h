#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>* board);

    wxArrayString getPossibleMoves() const override;
};
