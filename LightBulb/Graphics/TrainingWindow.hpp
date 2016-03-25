#pragma once

#ifndef _TRAININGWINDOW_H_
#define _TRAININGWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Graphics/AbstractWindow.hpp"
#include "TrainingController.hpp"

// Forward declarations
class wxRichTextCtrl;
class wxDataViewEvent;
class wxDataViewListCtrl;
class wxDataViewItem;

class TrainingWindow : public AbstractWindow
{
private:
	wxToolBar* toolbar;
	wxRichTextCtrl* detailsTextBox;
	wxDataViewListCtrl* neuralNetworkList;
	wxDataViewListCtrl* trainingPlanPatternList;
	wxDataViewListCtrl* trainingPlanList;
	std::unique_ptr<TrainingController> controller;
	wxChoice* neuralNetworksChoice;
	wxChoice* trainingPlanPatternsChoice;
	wxPanel* createNNColumn(wxWindow* parent);
	wxPanel* createTrainingColumn(wxWindow* parent);
	wxPanel* createRunningTrainingColumn(wxWindow* parent);
	wxPanel* createDetailsPanel(wxWindow* parent);
	void createMenuBar();
	void selectNeuralNetwork(wxDataViewEvent& event);
	void selectTrainingPlanPattern(wxDataViewEvent& event);
	void showProcessOfTrainingPlan(AbstractTrainingPlan* trainingPlan);
	void restoreDefaultProcessView();
	void selectTrainingPlan(wxDataViewEvent& event);
	void showDetailsOfNeuralNetwork(AbstractNeuralNetwork* neuralNetwork);
	void showDetailsOfTrainingPlanPattern(AbstractTrainingPlan* trainingPlan);
	void showDetailsOfTrainingPlan(AbstractTrainingPlan* trainingPlan);
	void clearDetails();
	std::string getNeuralNetworkSizeAsString(std::vector<unsigned int> size);
	int getRowIndexOfItem(wxDataViewListCtrl* list, wxDataViewItem& item);
	void startTraining(wxCommandEvent& event);
	void pauseTraining(wxCommandEvent& event);

protected:
	DECLARE_EVENT_TABLE();
public:
	TrainingWindow();
	void refreshNeuralNetworks();
	void refreshTrainingPlanPatterns();
	void refreshTrainingPlans();
	void refreshAllData();
};

#endif
