// Includes
#include "Graphics/TrainingWindow.hpp"
#include <wx/dataview.h>
#include <wx/splitter.h>
#include <wx/artprov.h>
#include <wx/statline.h>
#include <wx/richtext/richtextctrl.h>

BEGIN_EVENT_TABLE(TrainingWindow, wxFrame)
EVT_BUTTON(wxID_NEW, TrainingWindow::OnClick)
END_EVENT_TABLE()

TrainingWindow::TrainingWindow()
{
	createMenuBar();

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxSplitterWindow* mainSplitterWindow = new wxSplitterWindow(this, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	wxSplitterWindow* centerSplitterWindow = new wxSplitterWindow(mainSplitterWindow, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	wxSplitterWindow* rightSplitterWindow = new wxSplitterWindow(centerSplitterWindow, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	rightSplitterWindow->SplitVertically(createTrainingColumn(rightSplitterWindow), createRunningTrainingColumn(rightSplitterWindow));
	rightSplitterWindow->SetSashGravity(0.5); 

	centerSplitterWindow->SplitVertically(createNNColumn(centerSplitterWindow), rightSplitterWindow);
	centerSplitterWindow->SetSashGravity(0.3333);

	mainSplitterWindow->SplitHorizontally(centerSplitterWindow, createDetailsPanel(mainSplitterWindow));
	mainSplitterWindow->SetSashGravity(0.5);

	sizer->Add(mainSplitterWindow, 1, wxEXPAND);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}


wxPanel* TrainingWindow::createNNColumn(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticText(panel, -1, "Neural networks"), 0, wxEXPAND | wxALL, 5);

	wxDataViewListCtrl *listctrl = new wxDataViewListCtrl(panel, wxID_ANY);
	listctrl->AppendTextColumn("Name", wxDATAVIEW_CELL_EDITABLE)->SetMinWidth(50);
	listctrl->AppendTextColumn("Size")->SetMinWidth(50);
	listctrl->AppendTextColumn("Creation date")->SetMinWidth(50);
	wxVector<wxVariant> data;
	data.push_back(wxVariant("NN1"));
	data.push_back(wxVariant("8-3-9"));
	data.push_back(wxVariant("19.12.42 23:00"));
	listctrl->AppendItem(data);
	data.clear();
	data.push_back(wxVariant("NN2"));
	data.push_back(wxVariant("10-452-3"));
	data.push_back(wxVariant("03.12.32 13:03"));
	listctrl->AppendItem(data);

	listctrl->SetMinSize(wxSize(100, 100));

	sizer->Add(listctrl, 1, wxEXPAND, 0);
	panel->SetSizer(sizer);
	return panel;
}


wxPanel* TrainingWindow::createTrainingColumn(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticText(panel, -1, "Trainings"), 0, wxEXPAND | wxALL, 5);

	wxDataViewListCtrl *listctrl = new wxDataViewListCtrl(panel, wxID_ANY);
	listctrl->AppendTextColumn("Name")->SetMinWidth(50);
	listctrl->AppendTextColumn("Learning rate")->SetMinWidth(50);
	listctrl->AppendTextColumn("Description")->SetMinWidth(50);
	wxVector<wxVariant> data;
	data.push_back(wxVariant("T1"));
	data.push_back(wxVariant("Backpropagation"));
	data.push_back(wxVariant("Trains a AND-NN"));
	listctrl->AppendItem(data);
	data.clear();
	data.push_back(wxVariant("T2"));
	data.push_back(wxVariant("Evolution"));
	data.push_back(wxVariant("Learns TicTacToe"));
	listctrl->AppendItem(data);

	listctrl->SetMinSize(wxSize(100, 100));

	sizer->Add(listctrl, 1, wxEXPAND, 0);
	panel->SetSizer(sizer);
	return panel;
}

wxPanel* TrainingWindow::createRunningTrainingColumn(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticText(panel, -1, "Running trainings"), 0, wxEXPAND | wxALL, 5);

	wxDataViewListCtrl *listctrl = new wxDataViewListCtrl(panel, wxID_ANY);
	listctrl->AppendTextColumn("Training name")->SetMinWidth(50);
	listctrl->AppendTextColumn("Network name")->SetMinWidth(50);
	listctrl->AppendTextColumn("State")->SetMinWidth(50);
	wxVector<wxVariant> data;
	data.push_back(wxVariant("T1"));
	data.push_back(wxVariant("NN1"));
	data.push_back(wxVariant("Running"));
	listctrl->AppendItem(data);

	listctrl->SetMinSize(wxSize(100, 100));

	sizer->Add(listctrl, 1, wxEXPAND, 0);
	panel->SetSizer(sizer);
	return panel;
}

wxPanel* TrainingWindow::createDetailsPanel(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);
	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	wxSizer* commandSizer = new wxBoxSizer(wxVERTICAL);
	commandSizer->Add(new wxStaticText(panel, -1, "Commands"), 0, wxLEFT | wxBOTTOM, 10);
	commandSizer->AddStretchSpacer(1);

	wxSizer* processSizer = new wxBoxSizer(wxHORIZONTAL);

	wxChoice* networks = new wxChoice(panel, wxID_ANY);
	networks->Append("NN1");
	networks->Append("NN2");
	networks->Append("NN3");
	processSizer->Add(networks);
	processSizer->Add(new wxStaticBitmap(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_GO_FORWARD)), 0, wxALIGN_CENTRE_VERTICAL);
	wxChoice* training = new wxChoice(panel, wxID_ANY);
	training->Append("Training1");
	training->Append("Training2");
	training->Append("Training3");
	processSizer->Add(training);

	commandSizer->Add(processSizer, 0, wxEXPAND | wxALL, 20);
	commandSizer->AddStretchSpacer(1);

	wxToolBar* toolbar = new wxToolBar(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	toolbar->AddTool(wxID_CLOSE, "Start", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
	toolbar->AddTool(wxID_CLOSE, "Pause", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
	toolbar->Realize();
	commandSizer->Add(toolbar);

	sizer->Add(commandSizer, 0, wxEXPAND | wxTOP, 10);
	sizer->Add(new wxStaticLine(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVERTICAL), 0, wxEXPAND);

	wxSizer* detailsSizer = new wxBoxSizer(wxVERTICAL);
	detailsSizer->Add(new wxStaticText(panel, -1, "Details"), 0, wxBOTTOM, 10);
	detailsSizer->Add(new wxRichTextCtrl(panel, wxID_ANY, "BlaBla:\nTest: 1\nFoo: Bar\n1: -234.32", wxDefaultPosition, wxDefaultSize, wxRE_READONLY), 1, wxEXPAND);
	sizer->Add(detailsSizer, 1, wxEXPAND | wxALL, 10);

	panel->SetSizer(sizer);
	sizer->SetSizeHints(panel);
	return panel;
}

void TrainingWindow::createMenuBar()
{
	wxMenuBar* menubar = new wxMenuBar();
	wxMenu* file = new wxMenu;
	file->Append(wxID_OPEN);
	file->Append(wxID_SAVE);
	file->Append(wxID_EXIT);
	menubar->Append(file, "File");
	SetMenuBar(menubar);
}

void TrainingWindow::OnClick(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION);
}
