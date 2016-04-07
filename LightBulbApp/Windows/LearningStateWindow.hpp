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

wxDECLARE_EVENT(LSW_EVT_REFRESH_CHART, wxThreadEvent);

class LearningStateWindow : public AbstractWindow
{
private:
	wxBoxSizer* sizer;
	wxChoice* trainingPlansChoice;
	LearningStateController* controller;
	wxBoxSizer* dataSetsSizer;
	wxChartPanel* chartPanel;
	std::vector<wxCheckBox*> dataSetsCheckBoxes;
	void trainingPlanChanged(wxCommandEvent& event);
	void selectionChanged(wxCommandEvent& event);
	void refreshChart(wxThreadEvent& event);
public:
	LearningStateWindow(LearningStateController* controller_, AbstractWindow* parent = NULL);
	void refreshTrainingPlans();
};

#endif
