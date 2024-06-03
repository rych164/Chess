#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>* board);

    wxArrayString getPossibleMoves() const override;
};
