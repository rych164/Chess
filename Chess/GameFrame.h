#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <wx/wx.h>
#include <map>
#include <string>

// Forward declaration.
class MyFrame;
class Piece;

class GameFrame : public wxFrame {
public:
    GameFrame(MyFrame* parent, const wxString& title);
    void OnBackToMenu(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);

private:
    MyFrame* parentFrame;
    std::map<std::string, wxBitmap> LoadPieceImages(int areaSize);
    std::string GetPieceImageName(Piece* piece);
};
