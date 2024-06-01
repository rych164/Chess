#include "Piece.h"

Piece::Piece(bool isWhite, int x, int y) : white(isWhite), posX(x), posY(y){}

bool Piece::isWhite() const {
	return white;
}
void Piece::moveTo(int newX, int newY) {
	posX = newX;
	posY = newY;
}