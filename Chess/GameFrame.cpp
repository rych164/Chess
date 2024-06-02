#include "GameFrame.h"
#include "MyFrame.h"
#include "Area.h"
#include "ChessBoard.h"
#include <map>
#include <typeinfo>
#include <wx/mstream.h>  // For memory stream if needed
#include <wx/image.h>    // For image handler

GameFrame::GameFrame(MyFrame* parent, const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE), parentFrame(parent) {

    // Initialize the image handlers
    wxInitAllImageHandlers();

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL); // Use horizontal sizer to add log panel
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxButton* btnBackToMenu = new wxButton(panel, wxID_ANY, wxT("Back To Menu"));
    wxButton* btnSaveGame = new wxButton(panel, wxID_ANY, wxT("Save Game"));

    vbox->Add(btnBackToMenu, 0, wxEXPAND | wxALL, 5);
    vbox->Add(btnSaveGame, 0, wxEXPAND | wxALL, 5);

    vbox->AddSpacer(10);

    ChessBoard chessBoard;
    chessBoard.setupBoard();

    wxGridSizer* gridSizer = new wxGridSizer(8, 8, 0, 0);

    int width, height;
    GetSize(&width, &height);
    int areaSize = std::min((width - 20) / 8, (height - 100) / 8);

    // Load piece images and scale them
    std::map<std::string, wxBitmap> pieceImages = LoadPieceImages(areaSize);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            wxPanel* areaPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(areaSize, areaSize), wxBORDER_SIMPLE);
            areaPanel->SetBackgroundColour((row + col) % 2 ? *wxLIGHT_GREY : *wxYELLOW);

            wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

            Piece* piece = chessBoard.getPieceAt(row, col);

            char coordLetter = 'A' + col;
            int coordNumber = 8 - row;
            wxString coordinates = wxString::Format(wxT("%c%d"), coordLetter, coordNumber);

            wxString toolTipText = coordinates;
            if (piece) {
                wxString pieceType = piece->isWhite() ? "White" : "Black";
                pieceType += typeid(*piece).name();
                toolTipText += " - " + pieceType;

                wxBitmap pieceBitmap = pieceImages[GetPieceImageName(piece)];
                wxStaticBitmap* pieceImage = new wxStaticBitmap(areaPanel, wxID_ANY, pieceBitmap);
                panelSizer->AddStretchSpacer(1);
                panelSizer->Add(pieceImage, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
                panelSizer->AddStretchSpacer(1);
            }

            areaPanel->SetToolTip(toolTipText);
            areaPanel->SetSizer(panelSizer);

            gridSizer->Add(areaPanel, 1, wxEXPAND | wxALL);
        }
    }

    vbox->Add(gridSizer, 1, wxEXPAND | wxALL, 5);

    // Set up move log list control
    wxPanel* logPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(200, -1));
    wxBoxSizer* logSizer = new wxBoxSizer(wxVERTICAL);
    moveLogListCtrl = new wxListCtrl(logPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    moveLogListCtrl->InsertColumn(0, "Move", wxLIST_FORMAT_LEFT, 200);
    logSizer->Add(moveLogListCtrl, 1, wxEXPAND | wxALL, 5);
    logPanel->SetSizer(logSizer);

    // Add vbox and log panel to mainSizer
    mainSizer->Add(vbox, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(logPanel, 0, wxEXPAND | wxALL, 5);

    panel->SetSizer(mainSizer);
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

std::map<std::string, wxBitmap> GameFrame::LoadPieceImages(int areaSize) {
    std::map<std::string, wxBitmap> pieceImages;
    pieceImages["white_pawn"] = wxBitmap(wxImage(wxT("images/white_pawn.png")).Rescale(areaSize, areaSize));
    pieceImages["white_rook"] = wxBitmap(wxImage(wxT("images/white_rook.png")).Rescale(areaSize, areaSize));
    pieceImages["white_knight"] = wxBitmap(wxImage(wxT("images/white_knight.png")).Rescale(areaSize, areaSize));
    pieceImages["white_bishop"] = wxBitmap(wxImage(wxT("images/white_bishop.png")).Rescale(areaSize, areaSize));
    pieceImages["white_queen"] = wxBitmap(wxImage(wxT("images/white_queen.png")).Rescale(areaSize, areaSize));
    pieceImages["white_king"] = wxBitmap(wxImage(wxT("images/white_king.png")).Rescale(areaSize, areaSize));
    pieceImages["black_pawn"] = wxBitmap(wxImage(wxT("images/black_pawn.png")).Rescale(areaSize, areaSize));
    pieceImages["black_rook"] = wxBitmap(wxImage(wxT("images/black_rook.png")).Rescale(areaSize, areaSize));
    pieceImages["black_knight"] = wxBitmap(wxImage(wxT("images/black_knight.png")).Rescale(areaSize, areaSize));
    pieceImages["black_bishop"] = wxBitmap(wxImage(wxT("images/black_bishop.png")).Rescale(areaSize, areaSize));
    pieceImages["black_queen"] = wxBitmap(wxImage(wxT("images/black_queen.png")).Rescale(areaSize, areaSize));
    pieceImages["black_king"] = wxBitmap(wxImage(wxT("images/black_king.png")).Rescale(areaSize, areaSize));
    return pieceImages;
}

std::string GameFrame::GetPieceImageName(Piece* piece) {
    std::string color = piece->isWhite() ? "white" : "black";
    std::string pieceType = typeid(*piece).name();
    if (pieceType == "class Pawn") pieceType = "pawn";
    else if (pieceType == "class Rook") pieceType = "rook";
    else if (pieceType == "class Knight") pieceType = "knight";
    else if (pieceType == "class Bishop") pieceType = "bishop";
    else if (pieceType == "class Queen") pieceType = "queen";
    else if (pieceType == "class King") pieceType = "king";
    return color + "_" + pieceType;
}

void GameFrame::LogMove(const wxString& move) {
    long itemIndex = moveLogListCtrl->InsertItem(moveLogListCtrl->GetItemCount(), move);
    moveLogListCtrl->EnsureVisible(itemIndex);
}
