#pragma once

#include "Piece.h"
#include <vector>
#include <memory>

class Pawn : public Piece
{
public:
	const std::vector<std::vector<std::unique_ptr<Piece>>>& board;

	Pawn(bool isWhite, int x, int y, const std::vector<std::vector<std::unique_ptr<Piece>>>& boardRef);

	wxArrayString getPossibleMoves() const override;
};

