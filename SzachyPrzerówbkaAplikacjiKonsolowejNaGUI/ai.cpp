#include "ai.h"
#include "chess.h"
#include <algorithm>

std::pair<Position, Position> ChessAI::getBestMove(ChessGame& game) {
    int bestScore = -10000;
    std::pair<Position, Position> bestMove;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Position from = { row, col };
            if (game.board[row][col].color == game.currentPlayer) {
                std::vector<Position> possibleMoves = game.getPossibleMoves(from);
                for (auto& to : possibleMoves) {
                    Piece capturedPiece = game.board[to.row][to.col];
                    game.board[to.row][to.col] = game.board[from.row][from.col];
                    game.board[from.row][from.col] = { PieceType::None, Color::None };

                    int moveScore = minimax(game, 0, false);

                    game.board[from.row][from.col] = game.board[to.row][to.col];
                    game.board[to.row][to.col] = capturedPiece;

                    if (moveScore > bestScore) {
                        bestScore = moveScore;
                        bestMove = { from, to };
                    }
                }
            }
        }
    }

    return bestMove;
}

int ChessAI::minimax(ChessGame& game, int depth, bool isMaximizingPlayer) {
    if (depth == 3 || game.isCheckmate() || game.isStalemate()) {
        return game.evaluateBoard();
    }

    if (isMaximizingPlayer) {
        int bestScore = -10000;
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                Position from = { row, col };
                if (game.board[row][col].color == game.currentPlayer) {
                    std::vector<Position> possibleMoves = game.getPossibleMoves(from);
                    for (auto& to : possibleMoves) {
                        Piece capturedPiece = game.board[to.row][to.col];
                        game.board[to.row][to.col] = game.board[from.row][from.col];
                        game.board[from.row][from.col] = { PieceType::None, Color::None };

                        int moveScore = minimax(game, depth + 1, false);

                        game.board[from.row][from.col] = game.board[to.row][to.col];
                        game.board[to.row][to.col] = capturedPiece;

                        bestScore = std::max(bestScore, moveScore);
                    }
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = 10000;
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                Position from = { row, col };
                if (game.board[row][col].color != game.currentPlayer && game.board[row][col].color != Color::None) {
                    std::vector<Position> possibleMoves = game.getPossibleMoves(from);
                    for (auto& to : possibleMoves) {
                        Piece capturedPiece = game.board[to.row][to.col];
                        game.board[to.row][to.col] = game.board[from.row][from.col];
                        game.board[from.row][from.col] = { PieceType::None, Color::None };

                        int moveScore = minimax(game, depth + 1, true);

                        game.board[from.row][from.col] = game.board[to.row][to.col];
                        game.board[to.row][to.col] = capturedPiece;

                        bestScore = std::min(bestScore, moveScore);
                    }
                }
            }
        }
        return bestScore;
    }
}
