#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <map>
#include <string>
#include <memory>
#include "Player.h"
#include "ChessBoard.h"

// Forward declaration
class MyFrame;
class Piece;

class GameFrame : public wxFrame {
public:
    GameFrame(MyFrame* parent, const wxString& title);
    void OnBackToMenu(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void LogMove(const wxString& move);
    void OnPieceSelected(wxMouseEvent& event);

private:
    MyFrame* parentFrame;
    wxListCtrl* moveLogListCtrl;
    std::map<std::string, wxBitmap> LoadPieceImages(int areaSize);
    std::string GetPieceImageName(Piece* piece);

    ChessBoard chessBoard;
    Player currentPlayer;
    wxPanel* selectedPiecePanel;

    void HighlightPossibleMoves(Piece* piece);
    void ClearHighlights();
};
