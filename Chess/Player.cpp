#include "Player.h"

Player::Player(bool isWhite) : ifWhite(isWhite){}

bool Player::isWhite() const {
	return ifWhite;
}

void Player::setWhite(bool isWhite) {
	this->ifWhite = isWhite;
}