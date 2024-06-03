#include "Piece.h"

Piece::Piece(bool isWhite, int x, int y)
    : white(isWhite), posX(x), posY(y), board(nullptr) {}

bool Piece::isWhite() const {
    return white;
}

void Piece::moveTo(int newX, int newY) {
    posX = newX;
    posY = newY;
}

void Piece::setBoard(const std::vector<std::vector<std::unique_ptr<Piece>>>* boardRef) {
    board = boardRef;
}
