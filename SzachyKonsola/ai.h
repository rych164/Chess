#ifndef AI_H
#define AI_H

#include <utility>
#include "chess.h"

class ChessAI {
public:
    std::pair<Position, Position> getBestMove(ChessGame& game);

private:
    int minimax(ChessGame& game, int depth, bool isMaximizingPlayer);
};

#endif // AI_H
