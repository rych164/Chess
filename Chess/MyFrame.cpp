#include "MyFrame.h"
#include "GameFrame.h"



MyFrame::MyFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* fileMenu = new wxMenu;

	fileMenu->Append(ID_START_NEW_GAME, wxT("&Start New Game"));
	fileMenu->Append(ID_LOAD_GAME, wxT("&Load Game"));
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_EXIT, wxT("&Exit"));
	menuBar->Append(fileMenu, wxT("&File"));
	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText(wxT("Welcome To The Game"));

	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnStartNewGame, this, ID_START_NEW_GAME);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnLoadGame, this, ID_LOAD_GAME);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnExit, this, ID_EXIT);
}

void MyFrame::OnStartNewGame(wxCommandEvent& event)
{
	GameFrame* gameFrame = new GameFrame(this, wxT("Game Window"));
	gameFrame->Show();
	this->Hide();
}
void MyFrame::OnLoadGame(wxCommandEvent& event)
{
	wxMessageBox("Not Finnished yet");
}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}