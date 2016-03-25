// Includes
#include "Graphics/TrainingWindow.hpp"
#include <wx/dataview.h>
#include <wx/splitter.h>
#include <wx/artprov.h>
#include <wx/statline.h>
#include <wx/richtext/richtextctrl.h>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

enum
{
	TOOLBAR_START_TRAINING,
	TOOLBAR_PAUSE_TRAINING
};

BEGIN_EVENT_TABLE(TrainingWindow, wxFrame)
END_EVENT_TABLE()

TrainingWindow::TrainingWindow()
{
	controller.reset(new TrainingController(this));

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

	refreshAllData();
}


wxPanel* TrainingWindow::createNNColumn(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticText(panel, -1, "Neural networks"), 0, wxEXPAND | wxALL, 5);

	neuralNetworkList = new wxDataViewListCtrl(panel, wxID_ANY);
	neuralNetworkList->AppendTextColumn("Name", wxDATAVIEW_CELL_EDITABLE)->SetMinWidth(50);
	neuralNetworkList->AppendTextColumn("Size")->SetMinWidth(50);
	neuralNetworkList->AppendTextColumn("Creation date")->SetMinWidth(50);
	neuralNetworkList->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, wxObjectEventFunction(&TrainingWindow::selectNeuralNetwork), this);
	neuralNetworkList->SetMinSize(wxSize(100, 100));

	sizer->Add(neuralNetworkList, 1, wxEXPAND, 0);
	panel->SetSizer(sizer);
	return panel;
}


void TrainingWindow::refreshNeuralNetworks()
{
	neuralNetworkList->DeleteAllItems();
	neuralNetworksChoice->Clear();
	for (auto network = controller->getNeuralNetworks()->begin(); network != controller->getNeuralNetworks()->end(); network++)
	{
		wxVector<wxVariant> data;
		data.push_back(wxVariant((*network)->getName()));
		data.push_back(wxVariant(getNeuralNetworkSizeAsString((*network)->getNetworkTopology()->getNeuronCountsPerLayer())));
		std::time_t creationDate = (*network)->getCreationDate();
		data.push_back(wxVariant(std::asctime(std::localtime(&creationDate))));
		neuralNetworkList->AppendItem(data);
		neuralNetworksChoice->Append((*network)->getName());
	}
	neuralNetworksChoice->Append("<Create new>");
	neuralNetworksChoice->SetSelection(controller->getNeuralNetworks()->size());
}

wxPanel* TrainingWindow::createTrainingColumn(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticText(panel, -1, "Trainings"), 0, wxEXPAND | wxALL, 5);

	trainingPlanPatternList = new wxDataViewListCtrl(panel, wxID_ANY);
	trainingPlanPatternList->AppendTextColumn("Name")->SetMinWidth(50);
	trainingPlanPatternList->AppendTextColumn("Learning rate")->SetMinWidth(50);
	trainingPlanPatternList->AppendTextColumn("Description")->SetMinWidth(50);
	trainingPlanPatternList->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, wxObjectEventFunction(&TrainingWindow::selectTrainingPlanPattern), this);
	trainingPlanPatternList->SetMinSize(wxSize(100, 100));

	sizer->Add(trainingPlanPatternList, 1, wxEXPAND, 0);
	panel->SetSizer(sizer);
	return panel;
}


void TrainingWindow::refreshTrainingPlanPatterns()
{
	trainingPlanPatternList->DeleteAllItems();
	trainingPlanPatternsChoice->Clear();
	for (auto trainingPlan = controller->getTrainingPlanPatterns()->begin(); trainingPlan != controller->getTrainingPlanPatterns()->end(); trainingPlan++)
	{
		wxVector<wxVariant> data;
		data.push_back(wxVariant((*trainingPlan)->getName()));
		data.push_back(wxVariant((*trainingPlan)->getLearningRateName()));
		data.push_back(wxVariant((*trainingPlan)->getDescription()));
		trainingPlanPatternList->AppendItem(data);
		trainingPlanPatternsChoice->Append((*trainingPlan)->getName());
	}
}

wxPanel* TrainingWindow::createRunningTrainingColumn(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticText(panel, -1, "Running trainings"), 0, wxEXPAND | wxALL, 5);

	trainingPlanList = new wxDataViewListCtrl(panel, wxID_ANY);
	trainingPlanList->AppendTextColumn("Training name")->SetMinWidth(50);
	trainingPlanList->AppendTextColumn("Network name")->SetMinWidth(50);
	trainingPlanList->AppendTextColumn("State")->SetMinWidth(50);
	trainingPlanList->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, wxObjectEventFunction(&TrainingWindow::selectTrainingPlan), this);
	trainingPlanList->SetMinSize(wxSize(100, 100));

	sizer->Add(trainingPlanList, 1, wxEXPAND, 0);
	panel->SetSizer(sizer);
	return panel;
}


void TrainingWindow::refreshTrainingPlans()
{
	trainingPlanList->DeleteAllItems();
	for (auto trainingPlan = controller->getTrainingPlans()->begin(); trainingPlan != controller->getTrainingPlans()->end(); trainingPlan++)
	{
		wxVector<wxVariant> data;
		data.push_back(wxVariant((*trainingPlan)->getName()));
		data.push_back(wxVariant((*trainingPlan)->getNeuralNetwork()->getName()));
		data.push_back(wxVariant((*trainingPlan)->getStateAsString()));
		trainingPlanList->AppendItem(data);
	}
}

void TrainingWindow::refreshAllData()
{
	refreshNeuralNetworks();
	refreshTrainingPlanPatterns();
	refreshTrainingPlans();
}

wxPanel* TrainingWindow::createDetailsPanel(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY);
	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	wxSizer* commandSizer = new wxBoxSizer(wxVERTICAL);
	commandSizer->Add(new wxStaticText(panel, -1, "Commands"), 0, wxLEFT | wxBOTTOM, 10);
	commandSizer->AddStretchSpacer(1);

	wxSizer* processSizer = new wxBoxSizer(wxHORIZONTAL);

	neuralNetworksChoice = new wxChoice(panel, wxID_ANY);
	processSizer->Add(neuralNetworksChoice);
	processSizer->Add(new wxStaticBitmap(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_GO_FORWARD)), 0, wxALIGN_CENTRE_VERTICAL);
	trainingPlanPatternsChoice = new wxChoice(panel, wxID_ANY);
	processSizer->Add(trainingPlanPatternsChoice);

	commandSizer->Add(processSizer, 0, wxEXPAND | wxALL, 20);
	commandSizer->AddStretchSpacer(1);

	toolbar = new wxToolBar(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	toolbar->AddTool(TOOLBAR_START_TRAINING, "Start", wxArtProvider::GetBitmap(wxART_GO_FORWARD));
	toolbar->AddTool(TOOLBAR_PAUSE_TRAINING, "Pause", wxArtProvider::GetBitmap(wxART_DELETE));
	toolbar->EnableTool(TOOLBAR_PAUSE_TRAINING, false);
	toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&TrainingWindow::startTraining), this, TOOLBAR_START_TRAINING);
	toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&TrainingWindow::pauseTraining), this, TOOLBAR_PAUSE_TRAINING);
	toolbar->Realize();
	commandSizer->Add(toolbar);

	sizer->Add(commandSizer, 0, wxEXPAND | wxTOP, 10);
	sizer->Add(new wxStaticLine(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVERTICAL), 0, wxEXPAND);

	wxSizer* detailsSizer = new wxBoxSizer(wxVERTICAL);
	detailsSizer->Add(new wxStaticText(panel, -1, "Details"), 0, wxBOTTOM, 10);
	detailsTextBox = new wxRichTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
	detailsSizer->Add(detailsTextBox, 1, wxEXPAND);
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

void TrainingWindow::selectNeuralNetwork(wxDataViewEvent& event)
{
	int row = getRowIndexOfItem(neuralNetworkList, event.GetItem());
	if (row != -1)
	{
		showDetailsOfNeuralNetwork((*controller->getNeuralNetworks())[row]);
		restoreDefaultProcessView();
		neuralNetworksChoice->Select(row);
	}
	else
		clearDetails();
}

void TrainingWindow::selectTrainingPlanPattern(wxDataViewEvent& event)
{
	int row = getRowIndexOfItem(trainingPlanPatternList, event.GetItem());
	if (row != -1) {
		showDetailsOfTrainingPlanPattern((*controller->getTrainingPlanPatterns())[row]);
		restoreDefaultProcessView();
		trainingPlanPatternsChoice->Select(row);
	}
	else
		clearDetails();
}

void TrainingWindow::showProcessOfTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	neuralNetworksChoice->Select(controller->getIndexOfNeuralNetwork(trainingPlan->getNeuralNetwork()));
	trainingPlanPatternsChoice->Select(controller->getIndexOfTrainingPlanPattern(trainingPlan->getTrainingPlanPattern()));
	neuralNetworksChoice->Enable(false);
	trainingPlanPatternsChoice->Enable(false);
	toolbar->EnableTool(TOOLBAR_START_TRAINING, false);
	toolbar->EnableTool(TOOLBAR_PAUSE_TRAINING, true);
}

void TrainingWindow::restoreDefaultProcessView()
{
	neuralNetworksChoice->Enable(true);
	trainingPlanPatternsChoice->Enable(true);
	toolbar->EnableTool(TOOLBAR_START_TRAINING, true);
	toolbar->EnableTool(TOOLBAR_PAUSE_TRAINING, false);
}

void TrainingWindow::selectTrainingPlan(wxDataViewEvent& event)
{
	int row = getRowIndexOfItem(trainingPlanList, event.GetItem());
	if (row != -1)
	{
		showDetailsOfTrainingPlan((*controller->getTrainingPlans())[row]);
		showProcessOfTrainingPlan((*controller->getTrainingPlans())[row]);
	}
	else
		clearDetails();
}

void TrainingWindow::showDetailsOfNeuralNetwork(AbstractNeuralNetwork* neuralNetwork)
{
	clearDetails();
	detailsTextBox->WriteText("Name: " + neuralNetwork->getName() + "\n");
	detailsTextBox->WriteText("Size: " + getNeuralNetworkSizeAsString(neuralNetwork->getNetworkTopology()->getNeuronCountsPerLayer()) + "\n");
	std::time_t creationDate = neuralNetwork->getCreationDate();
	detailsTextBox->WriteText("Creation date: " + std::string(std::asctime(std::localtime(&creationDate))) + "\n");
}

void TrainingWindow::showDetailsOfTrainingPlanPattern(AbstractTrainingPlan* trainingPlan)
{
	clearDetails();
	detailsTextBox->WriteText("Name: " + trainingPlan->getName() + "\n");
	detailsTextBox->WriteText("Learning rate: " + trainingPlan->getLearningRateName() + "\n");
	detailsTextBox->WriteText("Description: " + trainingPlan->getDescription() + "\n");
}

void TrainingWindow::showDetailsOfTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	clearDetails();
	detailsTextBox->WriteText("Name: " + trainingPlan->getName() + "\n");
	detailsTextBox->WriteText("Network name: " + trainingPlan->getNeuralNetwork()->getName() + "\n");
	detailsTextBox->WriteText("State: " + trainingPlan->getStateAsString() + "\n");
}

void TrainingWindow::clearDetails()
{
	detailsTextBox->Clear();
}

std::string TrainingWindow::getNeuralNetworkSizeAsString(std::vector<unsigned int> size)
{
	std::string neuronCountsPerLayerString = "";
	for (int i = 0; i < size.size(); i++)
	{
		if (i != 0)
			neuronCountsPerLayerString += "-";
		neuronCountsPerLayerString += std::to_string(size[i]);
	}
	return neuronCountsPerLayerString;
}

int TrainingWindow::getRowIndexOfItem(wxDataViewListCtrl* list, wxDataViewItem& item)
{
	return ((wxDataViewIndexListModel*)list->GetModel())->GetRow(item);
}

void TrainingWindow::startTraining(wxCommandEvent& event)
{
	int neuralNetworkIndex = neuralNetworksChoice->GetSelection();
	int trainingPlanPatternIndex = trainingPlanPatternsChoice->GetSelection();
	if (neuralNetworkIndex != -1 && trainingPlanPatternIndex != -1)
	{
		controller->startTrainingPlanPattern(trainingPlanPatternIndex, neuralNetworkIndex);
	}
}

void TrainingWindow::pauseTraining(wxCommandEvent& event)
{
	int trainingPlanIndex = trainingPlanPatternsChoice->GetSelection();
	if (trainingPlanIndex != -1)
	{
		controller->pauseTrainingPlan(trainingPlanIndex);
	}
}
