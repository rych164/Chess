#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	board.resize(8);
	for (auto& row : board)
	{
		row.resize(8);
	}
}

void ChessBoard::setupBoard() {
	board[0][0] = std::make_unique<Rook>(false, 0, 0);
	board[0][7] = std::make_unique<Rook>(false, 0, 7);
	board[7][0] = std::make_unique<Rook>(true, 7, 0);
	board[7][7] = std::make_unique<Rook>(true, 7, 7);
	board[0][1] = std::make_unique<Knight>(false, 0, 1);
	board[0][6] = std::make_unique<Knight>(false, 0, 6);
	board[7][1] = std::make_unique<Knight>(true, 7, 1);
	board[7][6] = std::make_unique<Knight>(true, 7, 6);
}

Piece* ChessBoard::getPieceAt(int x, int y) const {
	return board[x][y].get();
}
