#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(bool isWhite, int x, int y);

	wxArrayString getPossibleMoves() const override;
};

