#include "GameFrame.h"
#include "MyFrame.h"

GameFrame::GameFrame(MyFrame* parent, const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE), parentFrame(parent) {
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	wxButton* btnBackToMenu = new wxButton(panel, wxID_ANY, wxT("Back To Menu"));
	wxButton* btnSaveGame = new wxButton(panel, wxID_ANY, wxT("Save Game"));

	vbox->Add(btnBackToMenu, 0, wxEXPAND | wxALL, 5);
	vbox->Add(btnSaveGame, 0, wxEXPAND | wxALL, 5);

	panel->SetSizer(vbox);
	panel->Layout();

	btnBackToMenu->Bind(wxEVT_BUTTON, &GameFrame::OnBackToMenu, this);
	btnSaveGame->Bind(wxEVT_BUTTON, &GameFrame::OnSave, this);

	Maximize(true);
}

void GameFrame::OnBackToMenu(wxCommandEvent& event) {
	this->Hide();
	parentFrame->Show();
}

void GameFrame::OnSave(wxCommandEvent& event) {
	wxMessageBox("Save function not implemented yet");
}
