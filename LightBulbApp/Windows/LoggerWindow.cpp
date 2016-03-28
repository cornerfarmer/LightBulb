// Includes
#include "Windows/LoggerWindow.hpp"
#include <wx/richtext/richtextctrl.h>

LoggerWindow::LoggerWindow(LoggerController* controller_, AbstractWindow* parent)
	:AbstractWindow("Logger", parent)
{
	controller = controller_;

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	
	textBox = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 300), wxRE_READONLY);
	sizer->Add(textBox, 1, wxEXPAND);

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void LoggerWindow::addLogMessage(std::string message)
{
	textBox->AppendText(message + "\n");
}
