#pragma once

#include <wx/wx.h>

enum {
	ID_START_NEW_GAME = wxID_HIGHEST + 1,
	ID_LOAD_GAME,
	ID_EXIT,
};

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title);
	void OnStartNewGame(wxCommandEvent& event);
	void OnLoadGame(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

};
