#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(bool isWhite, int x, int y);

	wxArrayString getPossibleMoves() const override;
};

