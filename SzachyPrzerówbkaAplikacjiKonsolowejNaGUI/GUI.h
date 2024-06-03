#ifndef GUI_H
#define GUI_H

#include <wx/wx.h>
#include <wx/dcbuffer.h>  // Dodaj ten nag³ówek dla wxAutoBufferedPaintDC
#include "chess.h"
#include "ai.h"

class ChessFrame : public wxFrame {
public:
    ChessFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnPaint(wxPaintEvent& event);
    void OnClick(wxMouseEvent& event);
    void DrawBoard(wxDC& dc);
    void DrawPiece(wxDC& dc, Piece piece, int row, int col);

    ChessGame game;
    ChessAI ai;
    Position selectedPosition;
    bool isPieceSelected;

    wxDECLARE_EVENT_TABLE();
};

#endif // GUI_H
