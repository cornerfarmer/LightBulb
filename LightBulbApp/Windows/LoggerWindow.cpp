// Includes
#include "Windows/LoggerWindow.hpp"
#include <wx/richtext/richtextctrl.h>
#include "LoggerController.hpp"

wxDEFINE_EVENT(LW_EVT_ADD_MSG, wxThreadEvent);

LoggerWindow::LoggerWindow(LoggerController* controller_, AbstractWindow* parent)
	:AbstractWindow(LoggerController::getLabel(), parent)
{
	controller = controller_;

	Bind(LW_EVT_ADD_MSG, wxThreadEventFunction(&LoggerWindow::addLogMessage), this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);
	header->Add(new wxStaticText(this, wxID_ANY, "Log:"));
	header->AddStretchSpacer(1);
	trainingPlansChoice = new wxChoice(this, wxID_ANY);
	trainingPlansChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&LoggerWindow::trainingPlanChanged), this);
	header->Add(trainingPlansChoice, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
	wxChoice* logLevelChoice = new wxChoice(this, wxID_ANY);
	logLevelChoice->Append("High");
	logLevelChoice->Append("Medium");
	logLevelChoice->Append("Low");
	logLevelChoice->SetSelection(2);
	logLevelChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&LoggerWindow::logLevelChanged), this);
	header->Add(logLevelChoice);

	sizer->Add(header, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 7);
	textBox = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 300), wxRE_READONLY);
	sizer->Add(textBox, 1, wxEXPAND | wxALL, 7);

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void LoggerWindow::trainingPlanChanged(wxCommandEvent& event)
{
	controller->selectTrainingPlan(event.GetSelection());
}

void LoggerWindow::logLevelChanged(wxCommandEvent& event)
{
	controller->setLogLevel(event.GetSelection());
}


void LoggerWindow::addLogMessage(wxThreadEvent& event)
{
	wxString message = event.GetPayload<wxString>();
	textBox->AppendText(message + "\n");
}

void LoggerWindow::clearLog()
{
	textBox->Clear();
}

void LoggerWindow::refreshTrainingPlans()
{
	trainingPlansChoice->Clear();
	for (auto network = controller->getTrainingPlans()->begin(); network != controller->getTrainingPlans()->end(); network++)
	{
		trainingPlansChoice->Append((*network)->getName());
	}
	refreshAfterChange(GetSizer());
}
