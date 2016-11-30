#pragma once

#ifndef _LEARNINGSTATEWINDOW_H_
#define _LEARNINGSTATEWINDOW_H_

// Library include
#include <memory>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// Includes
#include "Windows/AbstractSubAppWindow.hpp"

// Forward declarations
class XYSimpleDataset;
class wxChartPanel;
class wxDataViewListCtrl;
class wxDataViewEvent;

namespace LightBulb
{
	// Forward declarations
	class LearningStateController;

	wxDECLARE_EVENT(LSW_EVT_REFRESH_CHART, wxThreadEvent);
	/**
	 * \brief The window of the learning state sub app.
	 */
	class LearningStateWindow : public AbstractSubAppWindow
	{
	private:
		/**
		 * \brief The main sizer.
		 */
		wxBoxSizer* sizer;
		/**
		 * \brief The choice to select the training plan.
		 */
		wxChoice* trainingPlansChoice;
		/**
		 * \brief The list of all currently selected data sets.
		 */
		wxDataViewListCtrl* dataSetsList;
		/**
		 * \brief The panel where the chart is drawn on.
		 */
		wxChartPanel* chartPanel;
		/**
		 * \brief The choice to select the refresh rate.
		 */
		wxComboBox* refreshRateChoice;
		/**
		 * \brief The choice to select the try number.
		 */
		wxChoice* tryChoice;
		/**
		 * \brief The choice to select the data set.
		 */
		wxChoice* dataSetChoice;
		/**
		 * \brief The choice to select the comparison dataset.
		 */
		wxChoice* comparisonDatasetChoice;
		/**
		 * \brief Is called after the training plan choice has changed.
		 * \param event The event data.
		 */
		void trainingPlanChanged(wxCommandEvent& event);
		/**
		* \brief Is called after the refresh rate choice has changed.
		* \param event The event data.
		*/
		void refreshRateChanged(wxCommandEvent& event);
		/**
		* \brief Is called after the comparison data set choice has changed.
		* \param event The event data.
		*/
		void comparisonDatasetChanged(wxCommandEvent& event);
		/**
		 * \brief Is called after the "add Dataset" button has been pressed.
		 * \param event The event data.
		 */
		void addDataSet(wxCommandEvent& event);
		/**
		 * \brief Is called when the chart should be refreshed.
		 * \param event The event data.
		 */
		void refreshChart(wxThreadEvent& event);
		/**
		 * \brief Is called after a right click on the data set list has been executed.
		 * \param event The event data.
		 */
		void dataSetsListRightClick(wxDataViewEvent& event);
		/**
		 * \brief Is called after a menu item on the data set popup menu has been selected.
		 * \param event The event data.
		 */
		void dataSetsPopUpMenuSelected(wxCommandEvent& event);
		/**
		 * \brief Refreshes the comparison data set choice.
		 */
		void refreshComparisonDatasetChoices();
		/**
		 * \brief Returns the corresponding controller.
		 * \return The controller.
		 */
		LearningStateController& getController();
	public:
		/**
		 * \brief Creates the window.
		 * \param controller_ The corresponding controller.
		 * \param parent The parent window.
		 */
		LearningStateWindow(LearningStateController& controller_, AbstractWindow& parent);
		/**
		 * \brief Refreshes the training plan choice.
		 */
		void refreshTrainingPlans();
	};
}

#endif
