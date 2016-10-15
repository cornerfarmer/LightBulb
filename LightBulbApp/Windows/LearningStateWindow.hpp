#pragma once

#ifndef _LEARNINGSTATEWINDOW_H_
#define _LEARNINGSTATEWINDOW_H_

// Library include
#include <memory>

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

	class LearningStateWindow : public AbstractSubAppWindow
	{
	private:
		wxBoxSizer* sizer;
		wxChoice* trainingPlansChoice;
		wxDataViewListCtrl* dataSetsList;
		wxChartPanel* chartPanel;
		wxComboBox* refreshRateChoice;
		wxChoice* tryChoice;
		wxChoice* dataSetChoice;
		wxChoice* comparisonDatasetChoice;
		void trainingPlanChanged(wxCommandEvent& event);
		void refreshRateChanged(wxCommandEvent& event);
		void comparisonDatasetChanged(wxCommandEvent& event);
		void addDataSet(wxCommandEvent& event);
		void refreshChart(wxThreadEvent& event);
		void dataSetsListRightClick(wxDataViewEvent& event);
		void dataSetsPopUpMenuSelected(wxCommandEvent& event);
		void refreshComparisonDatasetChoices();
		LearningStateController* getController();
	public:
		LearningStateWindow(LearningStateController* controller_, AbstractWindow* parent = nullptr);
		void refreshTrainingPlans();
	};
}

#endif
