#include <wx/wx.h>
#include "gui.h"

class ChessApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(ChessApp);

bool ChessApp::OnInit() {
    ChessFrame* frame = new ChessFrame("Chess Game", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}
