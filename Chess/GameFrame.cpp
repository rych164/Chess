#include "GameFrame.h"
#include "MyFrame.h"
#include "Area.h"
#include <typeinfo>
#include <wx/mstream.h>  // For memory stream if needed
#include <wx/image.h>    // For image handler

GameFrame::GameFrame(MyFrame* parent, const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE), parentFrame(parent), currentPlayer(true), selectedPiecePanel(nullptr) {

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
            areaPanel->SetName(coordinates);  // Ensure each panel is named with its coordinates

            panelMap[coordinates] = areaPanel;  // Add this line to populate the map

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

                pieceImage->Bind(wxEVT_LEFT_DOWN, &GameFrame::OnPieceSelected, this);
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

    LogMove("White's turn");

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

void GameFrame::OnPieceSelected(wxMouseEvent& event) {
    try {
        wxStaticBitmap* pieceImage = dynamic_cast<wxStaticBitmap*>(event.GetEventObject());
        if (!pieceImage) {
            wxLogError("OnPieceSelected: pieceImage is null.");
            return;
        }

        wxPanel* selectedPanel = dynamic_cast<wxPanel*>(pieceImage->GetParent());
        if (!selectedPanel) {
            wxLogError("OnPieceSelected: selectedPanel is null.");
            return;
        }

        wxToolTip* tooltip = selectedPanel->GetToolTip();
        if (!tooltip) {
            wxLogError("OnPieceSelected: tooltip is null.");
            return;
        }

        wxString tip = tooltip->GetTip();
        if (tip.Length() < 2) {
            wxLogError("OnPieceSelected: ToolTip format is incorrect.");
            return;
        }

        int row = 8 - (tip[1].GetValue() - '0');
        int col = tip[0].GetValue() - 'A';

        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            wxLogError("OnPieceSelected: Coordinates out of bounds.");
            return;
        }

        Piece* selectedPiece = chessBoard.getPieceAt(row, col);
        if (selectedPiece && selectedPiece->isWhite() == currentPlayer) {
            ClearHighlights(); // Clear previous highlights
            selectedPiecePanel = selectedPanel;
            selectedPanel->SetBackgroundColour(*wxBLUE); // Highlight the selected piece
            selectedPanel->Refresh();
            selectedPanel->Update();
            HighlightPossibleMoves(selectedPiece);
        }
        else {
            wxLogError("OnPieceSelected: Selected piece is null or does not match current player's color.");
        }
    }
    catch (const std::exception& e) {
        wxLogError("Exception caught in OnPieceSelected: %s", e.what());
    }
    catch (...) {
        wxLogError("Unknown exception caught in OnPieceSelected.");
    }
}

void GameFrame::HighlightPossibleMoves(Piece* piece) {
    try {
        wxArrayString possibleMoves = piece->getPossibleMoves();

        for (const auto& move : possibleMoves) {
            int row, col;
            if (sscanf(move.c_str(), "Move to (%d,%d)", &row, &col) == 2) {
                wxString coordinates = wxString::Format(wxT("%c%d"), 'A' + col, 8 - row);
                wxLogDebug("Highlighting possible move area at coordinates: %s", coordinates);
                wxPanel* targetPanel = panelMap[coordinates];  // Use the map to find the panel
                if (targetPanel) {
                    targetPanel->Bind(wxEVT_LEFT_DOWN, &GameFrame::OnMoveSelected, this);
                    targetPanel->SetBackgroundColour(*wxGREEN); // Highlight possible move areas
                    targetPanel->Refresh();
                    targetPanel->Update();
                    wxLogDebug("Highlighted panel at row: %d, col: %d", row, col);
                }
                else {
                    wxLogError("HighlightPossibleMoves: targetPanel is null for coordinates %s.", coordinates);
                }
            }
            else {
                wxLogError("HighlightPossibleMoves: Failed to parse move coordinates from string '%s'.", move.c_str());
            }
        }
    }
    catch (const std::exception& e) {
        wxLogError("Exception caught in HighlightPossibleMoves: %s", e.what());
    }
    catch (...) {
        wxLogError("Unknown exception caught in HighlightPossibleMoves.");
    }
}

void GameFrame::ClearHighlights() {
    try {
        for (auto& entry : panelMap) {
            wxPanel* panel = entry.second;
            if (panel) {
                wxString tip = panel->GetToolTip()->GetTip();
                if (!tip.IsEmpty() && tip.Length() >= 2) {
                    int row = 8 - (tip[1].GetValue() - '0');
                    int col = tip[0].GetValue() - 'A';
                    panel->SetBackgroundColour((row + col) % 2 ? *wxLIGHT_GREY : *wxYELLOW);
                    panel->Refresh();
                    panel->Update();
                }
            }
        }
        if (selectedPiecePanel) {
            wxString tip = selectedPiecePanel->GetToolTip()->GetTip();
            if (!tip.IsEmpty() && tip.Length() >= 2) {
                int row = 8 - (tip[1].GetValue() - '0');
                int col = tip[0].GetValue() - 'A';
                selectedPiecePanel->SetBackgroundColour((row + col) % 2 ? *wxLIGHT_GREY : *wxYELLOW);
                selectedPiecePanel->Refresh();
                selectedPiecePanel->Update();
            }
            selectedPiecePanel = nullptr;
        }
    }
    catch (const std::exception& e) {
        wxLogError("Exception caught in ClearHighlights: %s", e.what());
    }
    catch (...) {
        wxLogError("Unknown exception caught in ClearHighlights.");
    }
}

wxWindow* GameFrame::FindWindowByLabel(const wxString& label) {
    auto it = panelMap.find(label);
    if (it != panelMap.end()) {
        return it->second;
    }
    return nullptr;
}
void GameFrame::OnMoveSelected(wxMouseEvent& event) {
    wxPanel* movePanel = dynamic_cast<wxPanel*>(event.GetEventObject());
    if (!movePanel) {
        wxLogError("Move Panel is null.");
        return;
    }

    // Extract the coordinates from the panel's name or tooltip
    wxString coordinates = movePanel->GetName();
    int row = 8 - (coordinates[1].GetValue() - '0');
    int col = coordinates[0].GetValue() - 'A';

    // Now perform the move using these coordinates and the stored selected piece
    if (selectedPiecePanel && selectedPiecePanel->GetName() != coordinates) {
        Piece* selectedPiece = chessBoard.getPieceAt(8 - (selectedPiecePanel->GetName()[1].GetValue() - '0'), selectedPiecePanel->GetName()[0].GetValue() - 'A');
        if (selectedPiece) {
            selectedPiece->moveTo(row, col);  // Update the internal state
            UpdateGUIAfterMove(selectedPiecePanel, movePanel); // You need to implement this
            ClearHighlights();
            TogglePlayerTurn(); // You need to implement this
        }
    }
}
void GameFrame::UpdateGUIAfterMove(wxPanel* sourcePanel, wxPanel* destinationPanel) {
    wxString srcToolTip = sourcePanel->GetToolTip()->GetTip();
    wxString destToolTip = destinationPanel->GetToolTip()->GetTip();

    // Get coordinates to find pieces
    int srcRow = 8 - (srcToolTip[1].GetValue() - '0');
    int srcCol = srcToolTip[0].GetValue() - 'A';
    int destRow = 8 - (destToolTip[1].GetValue() - '0');
    int destCol = destToolTip[0].GetValue() - 'A';

    // Get the piece from the source panel
    Piece* piece = chessBoard.getPieceAt(srcRow, srcCol);
    if (!piece) {
        wxLogError("No piece at the source coordinates.");
        return;
    }

    // Move the piece in the board data structure
    chessBoard.movePiece(srcRow, srcCol, destRow, destCol); // This method needs to be implemented in ChessBoard

    // Update the destination panel with the new piece image
    wxStaticBitmap* sourceImage = dynamic_cast<wxStaticBitmap*>(sourcePanel->GetChildren().front());
    wxStaticBitmap* destinationImage = new wxStaticBitmap(destinationPanel, wxID_ANY, sourceImage->GetBitmap(), wxDefaultPosition, wxDefaultSize, 0);
    destinationPanel->GetSizer()->Add(destinationImage, 1, wxEXPAND | wxALL, 0);
    destinationPanel->Layout();

    // Clear the source panel
    sourcePanel->DestroyChildren();
    sourcePanel->SetBackgroundColour((srcRow + srcCol) % 2 ? *wxLIGHT_GREY : *wxYELLOW);
    sourcePanel->Refresh();

    // Log the move
    wxString moveDescription = wxString::Format("Moved from %c%d to %c%d", 'A' + srcCol, 8 - srcRow, 'A' + destCol, 8 - destRow);
    LogMove(moveDescription);
}
void GameFrame::TogglePlayerTurn() {
    currentPlayer = !currentPlayer; // Toggle the current player boolean
    wxString playerColor = currentPlayer ? "White's turn" : "Black's turn";
    LogMove(playerColor); // Log which player's turn it is now

    // Optionally, update any UI elements that indicate the current player
    // For example, changing the color of a status bar or a label
}
