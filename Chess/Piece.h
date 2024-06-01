#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"

class Piece
{
public:
	Piece(bool isWhite, int x, int y);

	bool isWhite() const;
	virtual void moveTo(int newX, int newY);
	virtual wxArrayString getPossibleMoves() const = 0;
protected:
	bool white;
	int posX;
	int posY;

};

