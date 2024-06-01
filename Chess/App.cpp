#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MyFrame* frame = new MyFrame("Chess Game");
	frame->Show(true);
	return true;
}

