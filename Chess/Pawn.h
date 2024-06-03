#pragma once

#include "Piece.h"
#include <vector>
#include <memory>

class Pawn : public Piece
{
public:
    Pawn(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>* board);

    wxArrayString getPossibleMoves() const override;
};
