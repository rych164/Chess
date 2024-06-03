#include <iostream>
#include "chess.h"
#include "ai.h"

int main() {
    ChessGame game;
    ChessAI ai;
    game.start(ai);
    return 0;
}
