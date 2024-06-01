#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>

class Area
{
public:
	Area(int size, char coordinationLetters, int coordinationNumbers, const std::string& color, bool isOccupied)
		: size(size),coordinationLetters(coordinationLetters),coordinationNumbers(coordinationNumbers),
		color(color),isOccupied(isOccupied){}

	int getSize() const { return size; }
	char getCoordinationLetters() const { return coordinationLetters; }
	int getCoordinationNumbers() const { return coordinationNumbers; }
	std::string getColor() const { return color; }
	bool getIsOccupied() const { return isOccupied; }

	void setSize(int newSize) { size = newSize; }
	void setCoordinationLetters(char newCoordinationLetters) { coordinationLetters = newCoordinationLetters; }
	void setCoordinationNumbers(int newCoordinationNumbers) { coordinationNumbers = newCoordinationNumbers; }
	void setColor(const std::string& newColor) { color = newColor; }
	void setIsOccupied(bool newIsOccupied) { isOccupied = newIsOccupied; }

private:
	int size;
	char coordinationLetters;
	int coordinationNumbers;
	std::string color;
	bool isOccupied;
};

