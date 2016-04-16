#pragma once

#ifndef _LOGGERWINDOW_H_
#define _LOGGERWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractWindow.hpp"
#include <Logging/AbstractLogger.hpp>

// Forward declarations
class wxRichTextCtrl;
class LoggerController;
class AbstractTrainingPlan;

wxDECLARE_EVENT(LW_EVT_ADD_NEW_MSG, wxThreadEvent);
wxDECLARE_EVENT(LW_EVT_RELOAD_LOG, wxThreadEvent);

class LoggerWindow : public AbstractWindow
{
private:
	LoggerController* controller;
	wxRichTextCtrl* textBox;
	wxChoice* trainingPlansChoice;
	void trainingPlanChanged(wxCommandEvent& event);
	void logLevelChanged(wxCommandEvent& event);
	void autoScrollingChanged(wxCommandEvent& event);
	void addNewLogMessages(wxThreadEvent& event);
	void reloadLog(wxThreadEvent& event);
	int lastLogMessageIndex;
public:
	LoggerWindow(LoggerController* controller_, AbstractWindow* parent = NULL);
	void addLogMessage(std::string msg);
	void clearLog();
	void refreshTrainingPlans();
};

#endif
