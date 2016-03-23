// Includes
#include "Graphics/TrainingWindow.hpp"
#include <wx/dataview.h>
#include <wx/splitter.h>
#include <wx/artprov.h>
#include <wx/statline.h>
#include <wx/richtext/richtextctrl.h>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

BEGIN_EVENT_TABLE(TrainingWindow, wxFrame)
EVT_BUTTON(wxID_NEW, TrainingWindow::OnClick)
END_EVENT_TABLE()

TrainingWindow::TrainingWindow()
{
	controller.reset(new TrainingController());

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
	for (auto network = controller->getNeuralNetworks()->begin(); network != controller->getNeuralNetworks()->end(); network++)
	{
		wxVector<wxVariant> data;
		data.push_back(wxVariant((*network)->getName()));
		std::vector<unsigned int> neuronCountsPerLayer = (*network)->getNetworkTopology()->getNeuronCountsPerLayer();
		std::string neuronCountsPerLayerString = "";
		for (int i = 0; i < neuronCountsPerLayer.size(); i++)
		{
			if (i != 0)
				neuronCountsPerLayerString += "-";
			neuronCountsPerLayerString += std::to_string(neuronCountsPerLayer[i]);
		}
		data.push_back(wxVariant(neuronCountsPerLayerString));
		std::time_t creationDate = (*network)->getCreationDate();
		data.push_back(wxVariant(std::asctime(std::localtime(&creationDate))));
		listctrl->AppendItem(data);
	}

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
	for (auto trainingPlan = controller->getTrainingPlans()->begin(); trainingPlan != controller->getTrainingPlans()->end(); trainingPlan++)
	{
		wxVector<wxVariant> data;
		data.push_back(wxVariant((*trainingPlan)->getName()));
		data.push_back(wxVariant((*trainingPlan)->getLearningRateName()));
		data.push_back(wxVariant((*trainingPlan)->getDescription()));
		listctrl->AppendItem(data);
	}

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
	for (auto trainingPlan = controller->getTrainingPlans()->begin(); trainingPlan != controller->getTrainingPlans()->end(); trainingPlan++)
	{
		wxVector<wxVariant> data;
		data.push_back(wxVariant((*trainingPlan)->getName()));
		data.push_back(wxVariant((*trainingPlan)->getNeuralNetwork()->getName()));
		data.push_back(wxVariant((*trainingPlan)->getState()));
		listctrl->AppendItem(data);
	}

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
	for (auto network = controller->getNeuralNetworks()->begin(); network != controller->getNeuralNetworks()->end(); network++)
	{
		networks->Append((*network)->getName());
	}
	processSizer->Add(networks);
	processSizer->Add(new wxStaticBitmap(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_GO_FORWARD)), 0, wxALIGN_CENTRE_VERTICAL);
	wxChoice* trainingPlans = new wxChoice(panel, wxID_ANY);
	for (auto trainingPlan = controller->getTrainingPlans()->begin(); trainingPlan != controller->getTrainingPlans()->end(); trainingPlan++)
	{
		trainingPlans->Append((*trainingPlan)->getName());
	}
	processSizer->Add(trainingPlans);

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
