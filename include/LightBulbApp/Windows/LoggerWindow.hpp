#pragma once

#ifndef _LOGGERWINDOW_H_
#define _LOGGERWINDOW_H_

// Library include
#include <memory>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// Includes
#include "LightBulbApp/Windows/AbstractSubAppWindow.hpp"

// Forward declarations
class wxRichTextCtrl;

namespace LightBulb
{
	// Forward declarations
	class LoggerController;
	class AbstractTrainingPlan;

	wxDECLARE_EVENT(LW_EVT_ADD_NEW_MSG, wxThreadEvent);
	wxDECLARE_EVENT(LW_EVT_RELOAD_LOG, wxThreadEvent);
	/**
	 * \brief The window of the logger sub app.
	 */
	class LoggerWindow : public AbstractSubAppWindow
	{
	private:
		/**
		 * \brief The textbox which shows all messages.
		 */
		wxRichTextCtrl* textBox;
		/**
		 * \brief The choice to select the training plan whose messages should be shown.
		 */
		wxChoice* trainingPlansChoice;
		/**
		 * \brief The message of the last shown log message,
		 */
		int lastLogMessageIndex;
		/**
		 * \brief The checkbox to toggle auto scrolling.
		 */
		wxCheckBox* checkBox;
		/**
		 * \brief Is called after the training plan choice has been changed.
		 * \param event The event data.
		 */
		void trainingPlanChanged(wxCommandEvent& event);
		/**
		 * \brief Is called after the log level choice has been changed.
		 * \param event The event data.
		 */
		void logLevelChanged(wxCommandEvent& event);
		/**
		 * \brief Is called after the check box selection has been changed.
		 * \param event The event data.
		 */
		void autoScrollingChanged(wxCommandEvent& event);
		/**
		 * \brief Is called when new log messages should be added.
		 * \param event The event data.
		 */
		void addNewLogMessages(wxThreadEvent& event);
		/**
		 * \brief Is called when the whole log should be reloaded.
		 * \param event The event data.
		 */
		void reloadLog(wxThreadEvent& event);
		/**
		 * \brief Is called after the scroll position has been changed.
		 * \param event The event data.
		 */
		void scrollChanged(wxScrollWinEvent& event);
		/**
		 * \brief Returns the corresponding controller.
		 * \return The controller.
		 */
		LoggerController& getController();
	public:
		/**
		 * \brief Creates the logger window.
		 * \param controller_ The corresponding controller.
		 * \param parent The parent window.
		 */
		LoggerWindow(LoggerController& controller_, AbstractWindow& parent);
		/**
		 * \brief Adds the given log message.
		 * \param msg The new log message.
		 */
		void addLogMessage(const std::string& msg);
		/**
		 * \brief Clears the whole log.
		 */
		void clearLog();
		/**
		 * \brief Refreshes the training plan choice.
		 */
		void refreshTrainingPlans();
	};
}

#endif
