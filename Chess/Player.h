#pragma once
#define _CRT_SECURE_NO_WARNINGS

class Player
{
public:
	Player(bool isWhite);

	bool isWhite() const;

	void setWhite(bool isWhite);
private:
	bool ifWhite;
};

