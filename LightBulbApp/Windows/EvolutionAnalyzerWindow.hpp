#pragma once

#ifndef _EvolutionAnalyzerWINDOW_H_
#define _EvolutionAnalyzerWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractSubAppWindow.hpp"
#include <Logging/AbstractLogger.hpp>

wxDECLARE_EVENT(EAW_EVT_REFRESH, wxThreadEvent);

// Forward declarations
class EvolutionAnalyzerController;
class wxDataViewListCtrl;

class EvolutionAnalyzerWindow : public AbstractSubAppWindow
{
private:
	wxChoice* trainingPlansChoice;
	EvolutionAnalyzerController* getController();
	wxDataViewListCtrl* highscoreList;
	void refresh(wxThreadEvent& event);
public:
	EvolutionAnalyzerWindow(EvolutionAnalyzerController* controller_, AbstractWindow* parent = NULL);
	void trainingPlanChanged(wxCommandEvent& event);
	void refreshTrainingPlans();
};

#endif
