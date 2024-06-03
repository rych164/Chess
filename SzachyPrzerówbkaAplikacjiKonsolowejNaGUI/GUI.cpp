#include "gui.h"

wxBEGIN_EVENT_TABLE(ChessFrame, wxFrame)
EVT_PAINT(ChessFrame::OnPaint)
EVT_LEFT_DOWN(ChessFrame::OnClick)
wxEND_EVENT_TABLE()

ChessFrame::ChessFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), isPieceSelected(false) {
    game = ChessGame();
    ai = ChessAI();
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void ChessFrame::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    DrawBoard(dc);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece piece = game.board[row][col];
            if (piece.type != PieceType::None) {
                DrawPiece(dc, piece, row, col);
            }
        }
    }
}

void ChessFrame::DrawBoard(wxDC& dc) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            wxBrush brush(((row + col) % 2 == 0) ? *wxWHITE_BRUSH : wxBrush(wxColour(255, 255, 0))); // Zmieniono kolor na ¿ó³ty
            dc.SetBrush(brush);
            dc.DrawRectangle(col * 40, row * 40, 40, 40);
        }
    }
}

void ChessFrame::DrawPiece(wxDC& dc, Piece piece, int row, int col) {
    wxString pieceChar;
    switch (piece.type) {
    case PieceType::King: pieceChar = "K"; break;
    case PieceType::Queen: pieceChar = "Q"; break;
    case PieceType::Rook: pieceChar = "R"; break;
    case PieceType::Bishop: pieceChar = "B"; break;
    case PieceType::Knight: pieceChar = "N"; break;
    case PieceType::Pawn: pieceChar = "P"; break;
    default: pieceChar = ""; break;
    }
    if (piece.color == Color::Black) {
        pieceChar.MakeLower();
    }
    dc.DrawText(pieceChar, col * 40 + 15, row * 40 + 5);
}

void ChessFrame::OnClick(wxMouseEvent& event) {
    int col = event.GetX() / 40;
    int row = event.GetY() / 40;
    Position pos = { row, col };

    if (isPieceSelected) {
        if (game.movePiece(selectedPosition, pos)) {
            Refresh();
            if (game.isCheckmate()) {
                wxMessageBox("Checkmate!", "Game Over", wxOK | wxICON_INFORMATION);
            }
            else if (game.isStalemate()) {
                wxMessageBox("Stalemate!", "Game Over", wxOK | wxICON_INFORMATION);
            }
            else {
                game.switchPlayer();
                if (game.currentPlayer == Color::Black) {
                    std::pair<Position, Position> aiMove = ai.getBestMove(game);
                    game.movePiece(aiMove.first, aiMove.second);
                    Refresh();
                    game.switchPlayer();
                }
            }
        }
        isPieceSelected = false;
    }
    else {
        selectedPosition = pos;
        isPieceSelected = true;
    }
}
