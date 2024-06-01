#include "GameFrame.h"
#include "MyFrame.h"
#include "Area.h"

GameFrame::GameFrame(MyFrame* parent, const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE), parentFrame(parent) {
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	wxButton* btnBackToMenu = new wxButton(panel, wxID_ANY, wxT("Back To Menu"));
	wxButton* btnSaveGame = new wxButton(panel, wxID_ANY, wxT("Save Game"));

	vbox->Add(btnBackToMenu, 0, wxEXPAND | wxALL, 5);
	vbox->Add(btnSaveGame, 0, wxEXPAND | wxALL, 5);

	vbox->AddSpacer(10);

	wxGridSizer* gridSizer = new wxGridSizer(8, 8, 0, 0);

	int width, height;
	GetSize(&width, &height);
	int areaSize = std::min((width - 20) / 8, (height - 70) / 8);

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			wxPanel* areaPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(areaSize, areaSize), wxBORDER_SIMPLE);
			areaPanel->SetBackgroundColour((row + col) % 2 ? *wxLIGHT_GREY : *wxYELLOW);
			gridSizer->Add(areaPanel, 1, wxEXPAND | wxALL);
		}
	}

	vbox->Add(gridSizer, 1, wxEXPAND | wxALL, 5);

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
