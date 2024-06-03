#pragma once

#include <wx/wx.h>
#include <vector>
#include <memory>

// Forward declaration
class Piece;

class Piece
{
public:
    Piece(bool isWhite, int x, int y);
    virtual ~Piece() = default;

    bool isWhite() const;
    virtual void moveTo(int newX, int newY);
    virtual wxArrayString getPossibleMoves() const = 0;

    void setBoard(const std::vector<std::vector<std::unique_ptr<Piece>>>* boardRef);

protected:
    bool white;
    int posX;
    int posY;
    const std::vector<std::vector<std::unique_ptr<Piece>>>* board;
};
