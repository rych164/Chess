#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>* board);

    wxArrayString getPossibleMoves() const override;
};
