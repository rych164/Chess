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

	board[0][2] = std::make_unique<Bishop>(false, 0, 2);
	board[0][5] = std::make_unique<Bishop>(false, 0, 5);
	board[7][2] = std::make_unique<Bishop>(true, 7, 2);
	board[7][5] = std::make_unique<Bishop>(true, 7, 5);

	board[0][3] = std::make_unique<Queen>(false, 0, 3);
	board[7][3] = std::make_unique<Queen>(true, 7, 3);

	board[0][4] = std::make_unique<King>(false, 0, 4);
	board[7][4] = std::make_unique<King>(true, 7, 4);

}

Piece* ChessBoard::getPieceAt(int x, int y) const {
	return board[x][y].get();
}
