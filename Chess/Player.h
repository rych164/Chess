#pragma once

class Player
{
public:
	Player(bool isWhite);

	bool isWhite() const;

	void setWhite(bool isWhite);
private:
	bool ifWhite;
};

