#pragma once

#ifndef _EvolutionAnalyzerWINDOW_H_
#define _EvolutionAnalyzerWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractSubAppWindow.hpp"
#include <Logging/AbstractLogger.hpp>
#include <Learning/Evolution/AbstractIndividual.hpp>

// Forward declarations
class wxDataViewListCtrl;

namespace LightBulb
{
	wxDECLARE_EVENT(EAW_EVT_REFRESH, wxThreadEvent);

	// Forward declarations
	class EvolutionAnalyzerController;
	/**
	 * \brief The window of the evolution analyzer sub app.
	 */
	class EvolutionAnalyzerWindow : public AbstractSubAppWindow
	{
	private:
		/**
		 * \brief The choice of the training plan to view.
		 */
		wxChoice* trainingPlansChoice;
		/**
		 * \brief Returns the corresponding EvolutionAnalyzerController.
		 * \return The controller.
		 */
		EvolutionAnalyzerController& getController();
		/**
		 * \brief The data grid for displaying the highscore.
		 */
		wxDataViewListCtrl* highscoreList;
		/**
		 * \brief Refreshes highscore.
		 * \details Is called after the EAW_EVT_REFRESH event has been thrown.
		 * \param event The event data.
		 */
		void refresh(wxThreadEvent& event);
		/**
		 * \brief Converts the given evolution source to a readable string.
		 * \param source The source to convert.
		 * \return The string.
		 */
		std::string getEvolutionSourceAsString(EvolutionSource source);
	public:
		/**
		 * \brief Creates the EvolutionAnalyzerWindow.
		 * \param controller_ The corresponding controller.
		 * \param parent The parent window.
		 */
		EvolutionAnalyzerWindow(EvolutionAnalyzerController& controller_, AbstractWindow& parent);
		/**
		 * \brief Is called after the training plan choice has been changed.
		 * \param event The event data.
		 */
		void trainingPlanChanged(wxCommandEvent& event);
		/**
		 * \brief Rebuilds the training plan choice.
		 */
		void refreshTrainingPlans();
	};
}

#endif
