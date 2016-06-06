// Includes
#include "Windows/EvolutionAnalyzerWindow.hpp"
#include "EvolutionAnalyzerController.hpp"
#include <wx/dataview.h>

wxDEFINE_EVENT(EAW_EVT_REFRESH, wxThreadEvent);

EvolutionAnalyzerController* EvolutionAnalyzerWindow::getController()
{
	return static_cast<EvolutionAnalyzerController*>(controller);
}

EvolutionAnalyzerWindow::EvolutionAnalyzerWindow(EvolutionAnalyzerController* controller_, AbstractWindow* parent)
	:AbstractSubAppWindow(controller_, EvolutionAnalyzerController::getLabel(), parent)
{
	Bind(EAW_EVT_REFRESH, wxThreadEventFunction(&EvolutionAnalyzerWindow::refresh), this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);

	header->AddStretchSpacer(1);
	trainingPlansChoice = new wxChoice(this, wxID_ANY);
	trainingPlansChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&EvolutionAnalyzerWindow::trainingPlanChanged), this);
	header->Add(trainingPlansChoice, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);

	sizer->Add(header, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 7);

	highscoreList = new wxDataViewListCtrl(this, wxID_ANY);
	highscoreList->AppendTextColumn("Source")->SetMinWidth(50);
	highscoreList->AppendTextColumn("Fitness")->SetMinWidth(50);
	sizer->Add(highscoreList, 1, wxEXPAND | wxALL, 7);

	sizer->SetMinSize(wxSize(300, 300));

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void EvolutionAnalyzerWindow::trainingPlanChanged(wxCommandEvent& event)
{
	getController()->selectTrainingPlan(event.GetSelection());
}


void EvolutionAnalyzerWindow::refreshTrainingPlans()
{
	trainingPlansChoice->Clear();
	for (auto network = getController()->getTrainingPlans()->begin(); network != getController()->getTrainingPlans()->end(); network++)
	{
		trainingPlansChoice->Append((*network)->getName());
	}
	refreshAfterChange(GetSizer());
}


void EvolutionAnalyzerWindow::refresh(wxThreadEvent& event)
{
	auto state = getController()->getCurrentState();
	
	highscoreList->DeleteAllItems();
	for (auto entry = state->begin(); entry != state->end(); entry++)
	{
		wxVector<wxVariant> data;
		data.push_back(wxVariant(getEvolutionSourceAsString(entry->first)));
		data.push_back(wxVariant(std::to_string(entry->second)));
		highscoreList->AppendItem(data);
	}
}

std::string EvolutionAnalyzerWindow::getEvolutionSourceAsString(EvolutionSource source)
{
	switch (source)
	{
	case Creation:
		return "Creation";
	case Mutation:
		return "Mutation";
	case Recombination:
		return "Recombination";
	case Reuse:
		return "Reuse";
	default:
		return "";
	}
}
