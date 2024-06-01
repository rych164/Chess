#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(bool isWhite, int x, int y);

	wxArrayString getPossibleMoves() const override;
};

