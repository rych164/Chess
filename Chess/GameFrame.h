#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <wx/wx.h>
class MyFrame;  // Forward declaration.

class GameFrame : public wxFrame {
public:
    GameFrame(MyFrame* parent, const wxString& title);
    void OnBackToMenu(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);

private:
    MyFrame* parentFrame;
};

