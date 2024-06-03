#include "ChessBoard.h"

ChessBoard::ChessBoard() {
    board.resize(8);
    for (auto& row : board) {
        row.resize(8);
    }
}

void ChessBoard::setupBoard() {
    // Example for Rook
    board[0][0] = std::make_unique<Rook>(false, 0, 0, &board);
    board[0][0]->setBoard(&board);
    board[0][7] = std::make_unique<Rook>(false, 0, 7, &board);
    board[0][7]->setBoard(&board);
    board[7][0] = std::make_unique<Rook>(true, 7, 0, &board);
    board[7][0]->setBoard(&board);
    board[7][7] = std::make_unique<Rook>(true, 7, 7, &board);
    board[7][7]->setBoard(&board);

    // Example for Knight
    board[0][1] = std::make_unique<Knight>(false, 0, 1, &board);
    board[0][1]->setBoard(&board);
    board[0][6] = std::make_unique<Knight>(false, 0, 6, &board);
    board[0][6]->setBoard(&board);
    board[7][1] = std::make_unique<Knight>(true, 7, 1, &board);
    board[7][1]->setBoard(&board);
    board[7][6] = std::make_unique<Knight>(true, 7, 6, &board);
    board[7][6]->setBoard(&board);

    // Example for Bishop
    board[0][2] = std::make_unique<Bishop>(false, 0, 2, &board);
    board[0][2]->setBoard(&board);
    board[0][5] = std::make_unique<Bishop>(false, 0, 5, &board);
    board[0][5]->setBoard(&board);
    board[7][2] = std::make_unique<Bishop>(true, 7, 2, &board);
    board[7][2]->setBoard(&board);
    board[7][5] = std::make_unique<Bishop>(true, 7, 5, &board);
    board[7][5]->setBoard(&board);

    // Example for Queen
    board[0][3] = std::make_unique<Queen>(false, 0, 3, &board);
    board[0][3]->setBoard(&board);
    board[7][3] = std::make_unique<Queen>(true, 7, 3, &board);
    board[7][3]->setBoard(&board);

    // Example for King
    board[0][4] = std::make_unique<King>(false, 0, 4, &board);
    board[0][4]->setBoard(&board);
    board[7][4] = std::make_unique<King>(true, 7, 4, &board);
    board[7][4]->setBoard(&board);

    // Continue setting up other pieces...

    for (int i = 0; i < 8; i++) {
        board[1][i] = std::make_unique<Pawn>(false, 1, i, &board);
        board[1][i]->setBoard(&board);
        board[6][i] = std::make_unique<Pawn>(true, 6, i, &board);
        board[6][i]->setBoard(&board);
    }
}

Piece* ChessBoard::getPieceAt(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        wxLogError("getPieceAt: Invalid board coordinates (%d, %d)", x, y);
        return nullptr;
    }
    return board[x][y].get();
}
