#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Piece.h"

class Knight : public Piece 
{
public:
	Knight(bool isWhite, int x, int y);

	wxArrayString getPossibleMoves() const override;
};

