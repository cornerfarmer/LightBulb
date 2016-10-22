#pragma once

#ifndef _EvolutionAnalyzerWINDOW_H_
#define _EvolutionAnalyzerWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractSubAppWindow.hpp"
#include <Logging/AbstractLogger.hpp>
#include <Learning/Evolution/AbstractEvolutionObject.hpp>

// Forward declarations
class wxDataViewListCtrl;

namespace LightBulb
{
	wxDECLARE_EVENT(EAW_EVT_REFRESH, wxThreadEvent);

	// Forward declarations
	class EvolutionAnalyzerController;

	class EvolutionAnalyzerWindow : public AbstractSubAppWindow
	{
	private:
		wxChoice* trainingPlansChoice;
		EvolutionAnalyzerController& getController();
		wxDataViewListCtrl* highscoreList;
		void refresh(wxThreadEvent& event);
		std::string getEvolutionSourceAsString(EvolutionSource source);
	public:
		EvolutionAnalyzerWindow(EvolutionAnalyzerController& controller_, AbstractWindow& parent);
		void trainingPlanChanged(wxCommandEvent& event);
		void refreshTrainingPlans();
	};
}

#endif
