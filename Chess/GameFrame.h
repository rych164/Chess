#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <map>
#include <string>
#include "ChessBoard.h"
#include "Piece.h"

class MyFrame;

class GameFrame : public wxFrame {
public:
    GameFrame(MyFrame* parent, const wxString& title);
    void OnPieceSelected(wxMouseEvent& event);
    void OnBackToMenu(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void LogMove(const wxString& move);
    std::map<std::string, wxBitmap> LoadPieceImages(int areaSize);
    std::string GetPieceImageName(Piece* piece);

private:
    void HighlightPossibleMoves(Piece* piece);
    void ClearHighlights();
    wxWindow* FindWindowByLabel(const wxString& label);

    MyFrame* parentFrame;
    wxListCtrl* moveLogListCtrl;
    ChessBoard chessBoard;
    bool currentPlayer; // true for white, false for black
    wxPanel* selectedPiecePanel;
    std::map<wxString, wxPanel*> panelMap;
};
