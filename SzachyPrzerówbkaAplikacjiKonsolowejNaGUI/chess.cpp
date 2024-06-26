#include "chess.h"
#include "utils.h"
#include <iostream>

ChessGame::ChessGame() {
    initializeBoard();
    currentPlayer = Color::White;
}

void ChessGame::initializeBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = { PieceType::None, Color::None };
        }
    }

    for (int i = 0; i < 8; ++i) {
        board[1][i] = { PieceType::Pawn, Color::White };
        board[6][i] = { PieceType::Pawn, Color::Black };
    }

    board[0][0] = { PieceType::Rook, Color::White };
    board[0][7] = { PieceType::Rook, Color::White };
    board[7][0] = { PieceType::Rook, Color::Black };
    board[7][7] = { PieceType::Rook, Color::Black };

    board[0][1] = { PieceType::Knight, Color::White };
    board[0][6] = { PieceType::Knight, Color::White };
    board[7][1] = { PieceType::Knight, Color::Black };
    board[7][6] = { PieceType::Knight, Color::Black };

    board[0][2] = { PieceType::Bishop, Color::White };
    board[0][5] = { PieceType::Bishop, Color::White };
    board[7][2] = { PieceType::Bishop, Color::Black };
    board[7][5] = { PieceType::Bishop, Color::Black };

    board[0][3] = { PieceType::Queen, Color::White };
    board[7][3] = { PieceType::Queen, Color::Black };

    board[0][4] = { PieceType::King, Color::White };
    board[7][4] = { PieceType::King, Color::Black };
}

void ChessGame::switchPlayer() {
    currentPlayer = (currentPlayer == Color::White) ? Color::Black : Color::White;
}

bool ChessGame::movePiece(Position from, Position to) {
    if (!isValidMove(from, to)) {
        return false;
    }
    board[to.row][to.col] = board[from.row][from.col];
    board[from.row][from.col] = { PieceType::None, Color::None };
    return true;
}

bool ChessGame::isCheck() {
    Position kingPos;
    // Znajd� pozycj� kr�la obecnego gracza
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].type == PieceType::King && board[row][col].color == currentPlayer) {
                kingPos = { row, col };
                break;
            }
        }
    }

    // Sprawd�, czy jakakolwiek figura przeciwnika mo�e zaatakowa� pozycj� kr�la
    Color opponent = (currentPlayer == Color::White) ? Color::Black : Color::White;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].color == opponent) {
                std::vector<Position> possibleMoves = getPossibleMoves({ row, col });
                for (const Position& move : possibleMoves) {
                    if (move.row == kingPos.row && move.col == kingPos.col) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool ChessGame::isCheckmate() {
    if (!isCheck()) {
        return false;
    }

    // Sprawd�, czy obecny gracz ma jakiekolwiek legalne ruchy, kt�re wyprowadz� go z szacha
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].color == currentPlayer) {
                std::vector<Position> possibleMoves = getPossibleMoves({ row, col });
                for (const Position& move : possibleMoves) {
                    Piece originalPiece = board[move.row][move.col];
                    board[move.row][move.col] = board[row][col];
                    board[row][col] = { PieceType::None, Color::None };

                    bool stillInCheck = isCheck();

                    // Cofnij ruch
                    board[row][col] = board[move.row][move.col];
                    board[move.row][move.col] = originalPiece;

                    if (!stillInCheck) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
bool ChessGame::isStalemate() {
    if (isCheck()) {
        return false;
    }

    // Sprawd�, czy obecny gracz ma jakiekolwiek legalne ruchy
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].color == currentPlayer) {
                std::vector<Position> possibleMoves = getPossibleMoves({ row, col });
                for (const Position& move : possibleMoves) {
                    Piece originalPiece = board[move.row][move.col];
                    board[move.row][move.col] = board[row][col];
                    board[row][col] = { PieceType::None, Color::None };

                    bool stillInCheck = isCheck();

                    // Cofnij ruch
                    board[row][col] = board[move.row][move.col];
                    board[move.row][move.col] = originalPiece;

                    if (!stillInCheck) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


std::vector<Position> ChessGame::getPossibleMoves(Position pos) {
    std::vector<Position> moves;
    Piece piece = board[pos.row][pos.col];
    if (piece.type == PieceType::None || piece.color != currentPlayer) {
        return moves;
    }

    int directions[8][2] = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},    // Vertical and horizontal directions
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1}  // Diagonal directions
    };

    switch (piece.type) {
    case PieceType::Pawn:
    {
        int forward = (piece.color == Color::White) ? 1 : -1;
        Position oneStep = { pos.row + forward, pos.col };
        Position twoSteps = { pos.row + 2 * forward, pos.col };
        Position captureLeft = { pos.row + forward, pos.col - 1 };
        Position captureRight = { pos.row + forward, pos.col + 1 };

        if (isValidMove(pos, oneStep)) {
            moves.push_back(oneStep);
        }
        if ((pos.row == 1 && piece.color == Color::White) || (pos.row == 6 && piece.color == Color::Black)) {
            if (isValidMove(pos, twoSteps)) {
                moves.push_back(twoSteps);
            }
        }
        if (isValidMove(pos, captureLeft)) {
            moves.push_back(captureLeft);
        }
        if (isValidMove(pos, captureRight)) {
            moves.push_back(captureRight);
        }
    }
    break;
    case PieceType::Rook:
        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j < 8; ++j) {
                Position move = { pos.row + j * directions[i][0], pos.col + j * directions[i][1] };
                if (isValidMove(pos, move)) {
                    moves.push_back(move);
                }
                if (!isPathClear(pos, move) || board[move.row][move.col].type != PieceType::None) {
                    break;
                }
            }
        }
        break;
    case PieceType::Knight:
    {
        int knightMoves[8][2] = {
            {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
            {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
        };
        for (int i = 0; i < 8; ++i) {
            Position move = { pos.row + knightMoves[i][0], pos.col + knightMoves[i][1] };
            if (isValidMove(pos, move)) {
                moves.push_back(move);
            }
        }
    }
    break;
    case PieceType::Bishop:
        for (int i = 4; i < 8; ++i) {
            for (int j = 1; j < 8; ++j) {
                Position move = { pos.row + j * directions[i][0], pos.col + j * directions[i][1] };
                if (isValidMove(pos, move)) {
                    moves.push_back(move);
                }
                if (!isPathClear(pos, move) || board[move.row][move.col].type != PieceType::None) {
                    break;
                }
            }
        }
        break;
    case PieceType::Queen:
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 8; ++j) {
                Position move = { pos.row + j * directions[i][0], pos.col + j * directions[i][1] };
                if (isValidMove(pos, move)) {
                    moves.push_back(move);
                }
                if (!isPathClear(pos, move) || board[move.row][move.col].type != PieceType::None) {
                    break;
                }
            }
        }
        break;
    case PieceType::King:
        for (int i = 0; i < 8; ++i) {
            Position move = { pos.row + directions[i][0], pos.col + directions[i][1] };
            if (isValidMove(pos, move)) {
                moves.push_back(move);
            }
        }
        break;
    default:
        break;
    }
    return moves;
}

bool ChessGame::isValidMove(Position from, Position to) {
    if (from.row < 0 || from.row >= 8 || from.col < 0 || from.col >= 8 ||
        to.row < 0 || to.row >= 8 || to.col < 0 || to.col >= 8) {
        return false;
    }

    Piece piece = board[from.row][from.col];
    Piece targetPiece = board[to.row][to.col];

    if (piece.color != currentPlayer || (targetPiece.color == currentPlayer)) {
        return false;
    }

    int rowDiff = to.row - from.row;
    int colDiff = to.col - from.col;

    switch (piece.type) {
    case PieceType::Pawn:
        if (piece.color == Color::White) {
            if ((from.row == 1 && rowDiff == 2 && colDiff == 0 && targetPiece.type == PieceType::None) ||
                (rowDiff == 1 && colDiff == 0 && targetPiece.type == PieceType::None) ||
                (rowDiff == 1 && abs(colDiff) == 1 && targetPiece.color == Color::Black)) {
                return true;
            }
        }
        else {
            if ((from.row == 6 && rowDiff == -2 && colDiff == 0 && targetPiece.type == PieceType::None) ||
                (rowDiff == -1 && colDiff == 0 && targetPiece.type == PieceType::None) ||
                (rowDiff == -1 && abs(colDiff) == 1 && targetPiece.color == Color::White)) {
                return true;
            }
        }
        break;
    case PieceType::Rook:
        if ((rowDiff == 0 || colDiff == 0) && isPathClear(from, to)) {
            return true;
        }
        break;
    case PieceType::Knight:
        if ((abs(rowDiff) == 2 && abs(colDiff) == 1) || (abs(rowDiff) == 1 && abs(colDiff) == 2)) {
            return true;
        }
        break;
    case PieceType::Bishop:
        if (abs(rowDiff) == abs(colDiff) && isPathClear(from, to)) {
            return true;
        }
        break;
    case PieceType::Queen:
        if ((rowDiff == 0 || colDiff == 0 || abs(rowDiff) == abs(colDiff)) && isPathClear(from, to)) {
            return true;
        }
        break;
    case PieceType::King:
        if (abs(rowDiff) <= 1 && abs(colDiff) <= 1) {
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

bool ChessGame::isPathClear(Position from, Position to) {
    int rowStep = (to.row - from.row == 0) ? 0 : (to.row - from.row) / abs(to.row - from.row);
    int colStep = (to.col - from.col == 0) ? 0 : (to.col - from.col) / abs(to.col - from.col);

    int row = from.row + rowStep;
    int col = from.col + colStep;

    while (row != to.row || col != to.col) {
        if (board[row][col].type != PieceType::None) {
            return false;
        }
        row += rowStep;
        col += colStep;
    }

    return true;
}

int ChessGame::evaluateBoard() {
    int score = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece piece = board[i][j];
            int pieceValue = 0;
            switch (piece.type) {
            case PieceType::Pawn:
                pieceValue = 1;
                break;
            case PieceType::Knight:
            case PieceType::Bishop:
                pieceValue = 3;
                break;
            case PieceType::Rook:
                pieceValue = 5;
                break;
            case PieceType::Queen:
                pieceValue = 9;
                break;
            case PieceType::King:
                pieceValue = 1000;
                break;
            default:
                break;
            }
            if (piece.color == Color::Black) {
                pieceValue = -pieceValue;
            }
            score += pieceValue;
        }
    }
    return score;
}
