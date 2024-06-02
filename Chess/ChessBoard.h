#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <memory>
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

class ChessBoard
{
public:
	ChessBoard();
	void setupBoard();
	Piece* getPieceAt(int x, int y) const;
private:
	std::vector<std::vector<std::unique_ptr<Piece>>> board;
};



