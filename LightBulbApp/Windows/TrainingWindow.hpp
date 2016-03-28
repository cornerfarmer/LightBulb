#pragma once

#ifndef _TRAININGWINDOW_H_
#define _TRAININGWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractWindow.hpp"

// Forward declarations
class wxRichTextCtrl;
class wxDataViewEvent;
class wxDataViewListCtrl;
class wxDataViewItem;
class TrainingController;
class AbstractTrainingPlan;
class AbstractNeuralNetwork;

class TrainingWindow : public AbstractWindow
{
private:
	wxToolBar* toolbar;
	wxRichTextCtrl* detailsTextBox;
	wxStaticText* processErrorText;
	wxDataViewListCtrl* neuralNetworkList;
	wxDataViewListCtrl* trainingPlanPatternList;
	wxDataViewListCtrl* trainingPlanList;
	TrainingController* controller;
	wxChoice* neuralNetworksChoice;
	wxChoice* trainingPlanPatternsChoice;
	AbstractTrainingPlan* processTrainingPlanSelection;
	wxPanel* createNNColumn(wxWindow* parent);
	wxPanel* createTrainingColumn(wxWindow* parent);
	wxPanel* createRunningTrainingColumn(wxWindow* parent);
	wxPanel* createDetailsPanel(wxWindow* parent);
	wxMenu* windowsMenu;
	std::map<int, AbstractWindow*> subWindows;
	void validateSelectedProcess();
	void* currentDetailObject;
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
	void processSelecionHasChanged(wxCommandEvent& event);
	void toggleSubWindow(wxCommandEvent& event);
protected:
	DECLARE_EVENT_TABLE();
public:
	TrainingWindow(TrainingController* controller_);
	void refreshNeuralNetworks();
	void refreshTrainingPlanPatterns();
	void refreshTrainingPlans();
	void refreshAllData();
	void addSubWindow(AbstractWindow* newSubWindow);
};

#endif
