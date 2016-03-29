// Includes
#include "Windows/LoggerWindow.hpp"
#include <wx/richtext/richtextctrl.h>
#include "LoggerController.hpp"

LoggerWindow::LoggerWindow(LoggerController* controller_, AbstractWindow* parent)
	:AbstractWindow("Logger", parent)
{
	controller = controller_;

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);
	header->Add(new wxStaticText(this, wxID_ANY, "Log:"));
	header->AddStretchSpacer(1);
	wxChoice* logLevelChoice = new wxChoice(this, wxID_ANY);
	logLevelChoice->Append("High");
	logLevelChoice->Append("Medium");
	logLevelChoice->Append("Low");
	logLevelChoice->SetSelection(0);
	logLevelChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&LoggerWindow::logLevelChanged), this);
	header->Add(logLevelChoice);

	sizer->Add(header, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 7);
	textBox = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 300), wxRE_READONLY);
	sizer->Add(textBox, 1, wxEXPAND | wxALL, 7);

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void LoggerWindow::logLevelChanged(wxCommandEvent& event)
{
	controller->setLogLevel(event.GetSelection());
}

void LoggerWindow::addLogMessage(std::string message)
{
	textBox->AppendText(message + "\n");
}

void LoggerWindow::clearLog()
{
	textBox->Clear();
}
