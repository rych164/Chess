#include <wx/wx.h>

class MyApp : public wxApp
{
public: 
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title); 
	void OnStartNewGame(wxCommandEvent& event);
	void OnLoadGame(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
};

enum
{
	ID_START_NEW_GAME = 1,
	ID_LOAD_GAME,
	ID_EXIT,
};

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame("Game Menu");
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title) :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	wxButton* startBtn = new wxButton(panel, ID_START_NEW_GAME, wxT("Start New Game"));
	wxButton* loadBtn = new wxButton(panel, ID_LOAD_GAME, wxT("Load Game"));
	wxButton* exitBtn = new wxButton(panel, ID_EXIT, wxT("Exit"));

	vbox->Add(startBtn, 1, wxEXPAND | wxALL, 10);
	vbox->Add(loadBtn, 1, wxEXPAND | wxALL, 10);
	vbox->Add(exitBtn, 1, wxEXPAND | wxALL, 10);

	panel->SetSizer(vbox);

	Connect(ID_START_NEW_GAME, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnStartNewGame));
	Connect(ID_LOAD_GAME, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnLoadGame));
	Connect(ID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnExit));
}

void MyFrame::OnStartNewGame(wxCommandEvent& event)
{
	wxMessageBox("Starting New Game");
}
void MyFrame::OnLoadGame(wxCommandEvent& event)
{
	wxMessageBox("Loading game...");
}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

wxIMPLEMENT_APP(MyApp);