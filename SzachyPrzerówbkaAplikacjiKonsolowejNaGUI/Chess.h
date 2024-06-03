#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <string>

enum class PieceType { King, Queen, Rook, Bishop, Knight, Pawn, None };
enum class Color { White, Black, None };

struct Piece {
    PieceType type;
    Color color;
};

struct Position {
    int row;
    int col;
};

class ChessAI;

class ChessGame {
public:
    ChessGame();
    void initializeBoard();
    void switchPlayer();
    bool movePiece(Position from, Position to);
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    std::vector<Position> getPossibleMoves(Position pos);
    int evaluateBoard();

    Piece board[8][8];
    Color currentPlayer;
    friend class ChessAI;

private:
    bool isValidMove(Position from, Position to);
    bool isPathClear(Position from, Position to);
};

#endif // CHESS_H
