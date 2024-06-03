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
    void start(ChessAI& ai);
    void displayBoard();
    bool movePiece(Position from, Position to);
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);
    void switchPlayer();

private:
    Piece board[8][8];
    Color currentPlayer;
    bool isValidMove(Position from, Position to);
    bool isPathClear(Position from, Position to);
    void initializeBoard();
    std::vector<Position> getPossibleMoves(Position pos);
    int evaluateBoard();
    friend class ChessAI;
};

#endif // CHESS_H
