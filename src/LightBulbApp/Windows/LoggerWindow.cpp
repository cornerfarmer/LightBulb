// Includes
#include "Windows/LoggerWindow.hpp"
#include <wx/richtext/richtextctrl.h>
#include "LoggerController.hpp"

namespace LightBulb
{
	wxDEFINE_EVENT(LW_EVT_ADD_NEW_MSG, wxThreadEvent);
	wxDEFINE_EVENT(LW_EVT_RELOAD_LOG, wxThreadEvent);


	LoggerController& LoggerWindow::getController()
	{
		return static_cast<LoggerController&>(*controller);
	}

	LoggerWindow::LoggerWindow(LoggerController& controller_, AbstractWindow& parent)
		:AbstractSubAppWindow(controller_, LoggerController::getLabel(), parent)
	{
		Bind(LW_EVT_ADD_NEW_MSG, wxThreadEventFunction(&LoggerWindow::addNewLogMessages), this);
		Bind(LW_EVT_RELOAD_LOG, wxThreadEventFunction(&LoggerWindow::reloadLog), this);

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
		textBox->Bind(wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventFunction(&LoggerWindow::scrollChanged), this);
		textBox->Bind(wxEVT_SCROLLWIN_LINEUP, wxScrollWinEventFunction(&LoggerWindow::scrollChanged), this);
		textBox->Bind(wxEVT_SCROLLWIN_PAGEUP, wxScrollWinEventFunction(&LoggerWindow::scrollChanged), this);
		sizer->Add(textBox, 1, wxEXPAND | wxALL, 7);

		checkBox = new wxCheckBox(this, wxID_ANY, "Automatically scrolling");
		checkBox->SetValue(true);
		checkBox->Bind(wxEVT_CHECKBOX, wxCommandEventFunction(&LoggerWindow::autoScrollingChanged), this);
		sizer->Add(checkBox, 0, wxEXPAND | wxALL, 7);

		SetSizer(sizer);
		sizer->SetSizeHints(this);
	}

	void LoggerWindow::trainingPlanChanged(wxCommandEvent& event)
	{
		getController().selectTrainingPlan(event.GetSelection());
	}

	void LoggerWindow::logLevelChanged(wxCommandEvent& event)
	{
		getController().setLogLevel(event.GetSelection());
	}

	void LoggerWindow::autoScrollingChanged(wxCommandEvent& event)
	{
		getController().setAutoScrolling(event.GetSelection());
	}

	void LoggerWindow::addLogMessage(const std::string& msg)
	{
		textBox->AppendText(msg + "\n");
		if (textBox->GetNumberOfLines() > 2500)
			textBox->Remove(0, textBox->GetLineLength(0) + 1);
	}

	void LoggerWindow::clearLog()
	{
		textBox->Clear();
	}

	void LoggerWindow::refreshTrainingPlans()
	{
		trainingPlansChoice->Clear();
		for (auto network = getController().getTrainingPlans().begin(); network != getController().getTrainingPlans().end(); network++)
		{
			trainingPlansChoice->Append((*network)->getName());
		}
		refreshAfterChange(*GetSizer());
	}

	void LoggerWindow::addNewLogMessages(wxThreadEvent& event)
	{
		auto messages = getController().getMessages();
		for (int messageIndex = lastLogMessageIndex + 1; messageIndex < messages.size(); messageIndex++)
		{
			if (messages[messageIndex].first <= getController().getLogLevel())
				addLogMessage(messages[messageIndex].second);
			lastLogMessageIndex++;
		}
		if (getController().isAutoScrolling())
		{
			textBox->ScrollIntoView(textBox->GetLastPosition(), WXK_END);
		}
		getController().logMessagesAddingFinished();
	}

	void LoggerWindow::reloadLog(wxThreadEvent& event)
	{
		clearLog();
		lastLogMessageIndex = std::max(static_cast<int>(getController().getMessages().size() - 50), -1);
		addNewLogMessages(event);
	}

	void LoggerWindow::scrollChanged(wxScrollWinEvent& event)
	{
		if (getController().isAutoScrolling())
		{
			getController().setAutoScrolling(false);
			checkBox->SetValue(false);
		}
		event.Skip();
	}
}