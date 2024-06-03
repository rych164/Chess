#include "gui.h"

wxBEGIN_EVENT_TABLE(ChessFrame, wxFrame)
EVT_PAINT(ChessFrame::OnPaint)
EVT_LEFT_DOWN(ChessFrame::OnClick)
wxEND_EVENT_TABLE()

ChessFrame::ChessFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), isPieceSelected(false), turnNumber(1) {
    game = ChessGame();
    ai = ChessAI();
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxPanel* boardPanel = new wxPanel(this, wxID_ANY);
    boardPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);
    boardPanel->Bind(wxEVT_PAINT, &ChessFrame::OnPaint, this);
    boardPanel->Bind(wxEVT_LEFT_DOWN, &ChessFrame::OnClick, this);

    logCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, 600), wxTE_MULTILINE | wxTE_READONLY);

    sizer->Add(boardPanel, 1, wxEXPAND);
    sizer->Add(logCtrl, 0, wxEXPAND);

    SetSizerAndFit(sizer);
}

void ChessFrame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(static_cast<wxWindow*>(event.GetEventObject()));
    wxAutoBufferedPaintDC bdc(dc.GetWindow());
    bdc.Clear();
    DrawBoard(bdc);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece piece = game.board[row][col];
            if (piece.type != PieceType::None) {
                DrawPiece(bdc, piece, row, col);
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
    wxPanel* boardPanel = static_cast<wxPanel*>(event.GetEventObject());
    int col = event.GetX() / 40;
    int row = event.GetY() / 40;
    Position pos = { row, col };

    if (isPieceSelected) {
        Piece piece = game.board[selectedPosition.row][selectedPosition.col];
        wxString moveInfo;
        moveInfo.Printf("Turn %d: %s from (%d, %d) to (%d, %d)", turnNumber,
            piece.type == PieceType::King ? "King" :
            piece.type == PieceType::Queen ? "Queen" :
            piece.type == PieceType::Rook ? "Rook" :
            piece.type == PieceType::Bishop ? "Bishop" :
            piece.type == PieceType::Knight ? "Knight" :
            piece.type == PieceType::Pawn ? "Pawn" : "Unknown",
            selectedPosition.row, selectedPosition.col, pos.row, pos.col);

        if (game.movePiece(selectedPosition, pos)) {
            boardPanel->Refresh();
            if (game.isCheckmate()) {
                moveInfo += " - Checkmate!";
                wxMessageBox("Checkmate!", "Game Over", wxOK | wxICON_INFORMATION);
            }
            else if (game.isStalemate()) {
                moveInfo += " - Stalemate!";
                wxMessageBox("Stalemate!", "Game Over", wxOK | wxICON_INFORMATION);
            }
            else {
                game.switchPlayer();
                moveInfo += game.isCheck() ? " - Check!" : "";

                if (game.currentPlayer == Color::Black) {
                    std::pair<Position, Position> aiMove = ai.getBestMove(game);
                    game.movePiece(aiMove.first, aiMove.second);
                    moveInfo += wxString::Format("\nTurn %d: AI moved from (%d, %d) to (%d, %d)", turnNumber, aiMove.first.row, aiMove.first.col, aiMove.second.row, aiMove.second.col);
                    boardPanel->Refresh();
                    game.switchPlayer();
                }
            }
            turnNumber++;
            UpdateLog(moveInfo);
        }
        isPieceSelected = false;
    }
    else {
        selectedPosition = pos;
        isPieceSelected = true;
    }
}

void ChessFrame::UpdateLog(const wxString& logMessage) {
    logCtrl->AppendText(logMessage + "\n");
}
