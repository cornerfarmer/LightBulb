#pragma once

#ifndef _LEARNINGSTATEWINDOW_H_
#define _LEARNINGSTATEWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractWindow.hpp"

// Forward declarations
class LearningStateController;
class XYSimpleDataset;
class wxChartPanel;
class wxDataViewListCtrl;
class wxDataViewEvent;

wxDECLARE_EVENT(LSW_EVT_REFRESH_CHART, wxThreadEvent);

class LearningStateWindow : public AbstractWindow
{
private:
	wxBoxSizer* sizer;
	wxChoice* trainingPlansChoice;
	LearningStateController* controller;
	wxDataViewListCtrl* dataSetsList;
	wxChartPanel* chartPanel;
	wxComboBox* refreshRateChoice;
	wxChoice* tryChoice;
	wxChoice* dataSetChoice;
	void trainingPlanChanged(wxCommandEvent& event);
	void refreshRateChanged(wxCommandEvent& event);
	void addDataSet(wxCommandEvent& event);
	void refreshChart(wxThreadEvent& event);
	void dataSetsListRightClick(wxDataViewEvent& event);
	void dataSetsPopUpMenuSelected(wxCommandEvent& event);
public:
	LearningStateWindow(LearningStateController* controller_, AbstractWindow* parent = NULL);
	void refreshTrainingPlans();
};

#endif
