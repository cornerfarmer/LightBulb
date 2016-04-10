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

wxDECLARE_EVENT(LW_EVT_ADD_MSG, wxThreadEvent);

class LoggerWindow : public AbstractWindow
{
private:
	LoggerController* controller;
	wxRichTextCtrl* textBox;
	wxChoice* trainingPlansChoice;
	void trainingPlanChanged(wxCommandEvent& event);
	void logLevelChanged(wxCommandEvent& event);
public:
	LoggerWindow(LoggerController* controller_, AbstractWindow* parent = NULL);
	void addLogMessage(wxThreadEvent& event);
	void clearLog();
	void refreshTrainingPlans();
};

#endif
