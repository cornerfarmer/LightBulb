#pragma once

#ifndef _TRAININGWINDOW_H_
#define _TRAININGWINDOW_H_

// Library include
#include <memory>
#include <chrono>
#include <map>
// Includes
#include "Windows/AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

// Forward declarations
class wxRichTextCtrl;
class wxDataViewEvent;
class wxDataViewListCtrl;
class wxDataViewItem;

namespace LightBulb
{
	// Forward declarations
	class TrainingController;
	class AbstractTrainingPlan;
	class AbstractNeuralNetwork;

	wxDECLARE_EVENT(TW_EVT_REFRESH_NN, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_REFRESH_TPP, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_REFRESH_TP, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_REFRESH_ALL, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_SAVE_TP, wxThreadEvent);
	wxDECLARE_EVENT(TW_EVT_SAVE_TS, wxThreadEvent);

	class TrainingWindow : public AbstractWindow
	{
	private:
		wxToolBar* toolbar;
		wxRichTextCtrl* detailsTextBox;
		wxStaticText* processErrorText;
		wxDataViewListCtrl* neuralNetworkList;
		wxDataViewListCtrl* trainingPlanPatternList;
		wxDataViewListCtrl* trainingPlanList;
		wxChoice* neuralNetworksChoice;
		wxChoice* trainingPlanPatternsChoice;
		wxMenu* trainingPlanMenu;
		AbstractTrainingPlan* processTrainingPlanSelection;
		wxTimer* runTimeRefreshTimer;
		void fileMenuSelected(wxCommandEvent& event);
		void trainingPlanMenuSelected(wxCommandEvent& event);
		void neuralNetworkPopUpMenuSelected(wxCommandEvent& event);
		void neuralNetworkListRightClick(wxDataViewEvent& event);
		void trainingPlanPopUpMenuSelected(wxCommandEvent& event);
		void trainingPlanListRightClick(wxDataViewEvent& event);
		void trainingPlanNameChanged(wxDataViewEvent& event);
		wxPanel* createNNColumn(wxWindow* parent);
		wxPanel* createTrainingColumn(wxWindow* parent);
		wxPanel* createRunningTrainingColumn(wxWindow* parent);
		wxPanel* createDetailsPanel(wxWindow* parent);
		wxMenuBar* menubar;
		wxMenu* windowsMenu;
		bool customMenuVisible;
		std::map<int, AbstractWindow*> subWindows;
		void validateSelectedProcess();
		void* currentDetailObject;
		void createMenuBar();
		void selectNeuralNetwork(wxDataViewEvent& event);
		void selectTrainingPlanPattern(wxDataViewEvent& event);
		void showProcessOfTrainingPlan(AbstractTrainingPlan* trainingPlan);
		void restoreDefaultProcessView();
		void showCustomSubAppsMenuForTrainingPlan(AbstractTrainingPlan* trainingPlan);
		void selectTrainingPlan(wxDataViewEvent& event);
		void showDetailsOfNeuralNetwork(AbstractNeuralNetwork* neuralNetwork);
		void showDetailsOfTrainingPlanPattern(AbstractTrainingPlan* trainingPlan);
		void showDetailsOfTrainingPlan(AbstractTrainingPlan* trainingPlan);
		void clearDetails();
		std::string getNeuralNetworkSizeAsString(const std::vector<unsigned int>& size) const;
		int getRowIndexOfItem(const wxDataViewListCtrl* list, const wxDataViewItem& item) const;
		void startTraining(wxCommandEvent& event);
		void pauseTraining(wxCommandEvent& event);
		void showPreferences(wxCommandEvent& event);
		void processSelecionHasChanged(wxCommandEvent& event);
		void addSubApp(wxCommandEvent& event);
		void refreshNeuralNetworks(wxCommandEvent& event);
		void refreshTrainingPlanPatterns(wxCommandEvent& event);
		void refreshTrainingPlans(wxCommandEvent& event);
		void refreshAllData(wxCommandEvent& event);
		void saveTrainingPlan(wxThreadEvent& event);
		void saveTrainingSession(wxThreadEvent& event);
		void removeCustomSubAppsMenu();
		void refreshTrainingPlanRunTimes(wxTimerEvent& event);
		std::string getStringFromDuration(std::chrono::duration<double> duration) const;
		TrainingController* getController();
	protected:
		void close(wxCloseEvent& event);
		DECLARE_EVENT_TABLE();
	public:
		TrainingWindow(TrainingController* controller_);
		void addSubAppFactory(AbstractSubAppFactory* newSubAppFactory, int factoryIndex);
	};
}

#endif
