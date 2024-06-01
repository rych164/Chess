#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	board.resize(8);
	for (auto& row : board)
	{
		row.resize(8);
	}
}

void ChessBoard::setupBoard() {
	board[0][0] = std::make_unique<Rook>(true, 0, 0);
	board[0][7] = std::make_unique<Rook>(true, 0, 7);
	board[7][0] = std::make_unique<Rook>(true, 7, 0);
	board[7][7] = std::make_unique<Rook>(true, 7, 7);
}

Piece* ChessBoard::getPieceAt(int x, int y) const {
	return board[x][y].get();
}
