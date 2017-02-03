#pragma once

#ifndef _TRAININGWINDOW_H_
#define _TRAININGWINDOW_H_

// Library include
#include <memory>
#include <chrono>
#include <map>
// Includes
#include "LightBulbApp/Windows/AbstractWindow.hpp"

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
	class AbstractSubAppFactory;

	wxDECLARE_EVENT(TW_EVT_REFRESH_NN, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_REFRESH_TPP, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_REFRESH_TP, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_REFRESH_ALL, wxCommandEvent);
	wxDECLARE_EVENT(TW_EVT_SAVE_TP, wxThreadEvent);
	wxDECLARE_EVENT(TW_EVT_SAVE_TS, wxThreadEvent);
	wxDECLARE_EVENT(TW_EVT_LOAD_TS, wxThreadEvent);

	/**
	 * \brief The window of the training main app.
	 */
	class TrainingWindow : public AbstractWindow
	{
	private:
		/**
		 * \brief The main sizer.
		 */
		wxBoxSizer* mainSizer;
		/**
		 * \brief The bottom toolbar which controls training plans.
		 */
		wxToolBar* toolbar;
		/**
		 * \brief The textbox which shows details of the currently selected training plan.
		 */
		wxRichTextCtrl* detailsTextBox;
		/**
		 * \brief The error text of the current selected process.
		 */
		wxStaticText* processErrorText;
		/**
		 * \brief The neural network list.
		 */
		wxDataViewListCtrl* neuralNetworkList;
		/**
		 * \brief The training plan pattern list.
		 */
		wxDataViewListCtrl* trainingPlanPatternList;
		/**
		 * \brief The training plan list.
		 */
		wxDataViewListCtrl* trainingPlanList;
		/**
		 * \brief The choice which selects the training plan pattern to use.
		 */
		wxChoice* trainingPlanPatternsChoice;
		/**
		 * \brief The training plan menu.
		 */
		wxMenu* trainingPlanMenu;
		/**
		 * \brief The current selected training plan.
		 */
		AbstractTrainingPlan* processTrainingPlanSelection;
		/**
		 * \brief The timer which controls the refreshing rate.
		 */
		wxTimer runTimeRefreshTimer;
		/**
		 * \brief Is called after an item of the file menu has been selected.
		 * \param event The event data.
		 */
		void fileMenuSelected(wxCommandEvent& event);
		/**
		 * \brief Is called after an item of the training plan menu has been selected.
		 * \param event The event data.
		 */
		void trainingPlanMenuSelected(wxCommandEvent& event);
		/**
		 * \brief Is called after an item of the neural network pop up menu has been selected.
		 * \param event The event data.
		 */
		void neuralNetworkPopUpMenuSelected(wxCommandEvent& event);
		/**
		 * \brief Is called after a right click on the neural network list has been executed.
		 * \param event The event data.
		 */
		void neuralNetworkListRightClick(wxDataViewEvent& event);
		/**
		* \brief Is called after an item of the training plan pop up menu has been selected.
		* \param event The event data.
		*/
		void trainingPlanPopUpMenuSelected(wxCommandEvent& event);
		/**
		* \brief Is called after a right click on the training plan list has been executed.
		* \param event The event data.
		*/
		void trainingPlanListRightClick(wxDataViewEvent& event);
		/**
		 * \brief Is called after a training plan name has been changed.
		 * \param event The event data.
		 */
		void trainingPlanNameChanged(wxDataViewEvent& event);
		/**
		 * \brief Creates the neural network column.
		 * \param parent The parent element
		 * \return A new panel which contains the whole column.
		 */
		wxPanel* createNNColumn(wxWindow& parent);
		/**
		* \brief Creates the training plan pattern column.
		* \param parent The parent element
		* \return A new panel which contains the whole column.
		*/
		wxPanel* createTrainingColumn(wxWindow& parent);
		/**
		* \brief Creates the training plan column.
		* \param parent The parent element
		* \return A new panel which contains the whole column.
		*/
		wxPanel* createRunningTrainingColumn(wxWindow& parent);
		/**
		 * \brief Creates the details panel.
		 * \param parent The parent element
		 * \return A new panel which contains the details panel. 
		 */
		wxPanel* createDetailsPanel(wxWindow& parent);
		/**
		 * \brief The main menu bar.
		 */
		wxMenuBar* menubar;
		/**
		 * \brief The windows menu.
		 */
		wxMenu* windowsMenu;
		/**
		 * \brief Tells if the menu of custom sub apps is visible.
		 */
		bool customMenuVisible;
		/**
		 * \brief A pointer to the object whose detail are currently shown.
		 */
		void* currentDetailObject;
		/**
		 * \brief Creates the menu bar.
		 */
		void createMenuBar();
		/**
		 * \brief Is called after a network from the list has been selected. 
		 * \param event The event data.
		 */
		void selectNeuralNetwork(wxDataViewEvent& event);
		/**
		* \brief Is called after a training plan pattern from the list has been selected.
		* \param event The event data.
		*/
		void selectTrainingPlanPattern(wxDataViewEvent& event);
		/**
		 * \brief Shows the training plan process information.
		 * \param trainingPlan The training plan to show.
		 */
		void showProcessOfTrainingPlan(AbstractTrainingPlan& trainingPlan);
		/**
		 * \brief Restores the process window.
		 * \details Clears the toolbar and the choices.
		 */
		void restoreDefaultProcessView();
		/**
		 * \brief Show the custom sub app menu for the given training plan.
		 * \param trainingPlan The training plan to use.
		 */
		void showCustomSubAppsMenuForTrainingPlan(AbstractTrainingPlan& trainingPlan);
		/**
		 * \brief Is called after a training plan has been selected.
		 * \param event The event data.
		 */
		void selectTrainingPlan(wxDataViewEvent& event);
		/**
		 * \brief Show the detail info for the given network.
		 * \param neuralNetwork The network.
		 */
		void showDetailsOfNeuralNetwork(AbstractNeuralNetwork& neuralNetwork);
		/**
		* \brief Show the detail info for the given training plan pattern.
		* \param trainingPlan The training plan pattern.
		*/
		void showDetailsOfTrainingPlanPattern(AbstractTrainingPlan& trainingPlan);
		/**
		* \brief Show the detail info for the given training plan.
		* \param trainingPlan The training plan.
		*/
		void showDetailsOfTrainingPlan(AbstractTrainingPlan& trainingPlan);
		/**
		 * \brief Clears the detail window.
		 */
		void clearDetails();
		/**
		 * \brief Converts the layers sizes to a string.
		 * \param size The layer size vector.
		 * \return The string.
		 */
		std::string getNeuralNetworkSizeAsString(const std::vector<unsigned int>& size) const;
		/**
		 * \brief Returns the row index of the given item in the given list.
		 * \param list The list.
		 * \param item The item,
		 * \return The index of the item in the list.
		 */
		int getRowIndexOfItem(const wxDataViewListCtrl& list, const wxDataViewItem& item) const;
		/**
		 * \brief Is called after the start learning button has been pressed.
		 * \param event The event data.
		 */
		void startTraining(wxCommandEvent& event);
		/**
		* \brief Is called after the pause learning button has been pressed.
		* \param event The event data.
		*/
		void pauseTraining(wxCommandEvent& event);
		/**
		* \brief Is called after the show preferences button has been pressed.
		* \param event The event data.
		*/
		void showPreferences(wxCommandEvent& event);
		/**
		 * \brief Is called after the network or the training plan choice has been changed.
		 * \param event The event data.
		 */
		void processSelecionHasChanged(wxCommandEvent& event);
		/**
		 * \brief Is called after a item in the window menu has been selected.
		 * \param event The event data.
		 */
		void addSubApp(wxCommandEvent& event);
		/**
		 * \brief Refreshes the neural network list.
		 * \param event The event data.
		 */
		void refreshNeuralNetworks(wxCommandEvent& event);
		/**
		* \brief Refreshes the training plan pattern list.
		* \param event The event data.
		*/
		void refreshTrainingPlanPatterns(wxCommandEvent& event);
		/**
		* \brief Refreshes the training plan list.
		* \param event The event data.
		*/
		void refreshTrainingPlans(wxCommandEvent& event);
		/**
		 * \brief Refreshes all lists.
		 * \param event The event data.
		 */
		void refreshAllData(wxCommandEvent& event);
		/**
		 * \brief Saves the current selected training plan.
		 * \param event The event data.
		 */
		void saveTrainingPlan(wxThreadEvent& event);
		/**
		* \brief Saves the current training session.
		* \param event The event data.
		*/
		void saveTrainingSession(wxThreadEvent& event);
		/**
		* \brief Loads a training session.
		* \param event The event data.
		*/
		void loadTrainingSession(wxThreadEvent& event);
		/**
		 * \brief Removes the custom sub app menu.
		 */
		void removeCustomSubAppsMenu();
		/**
		 * \brief Refresh the stats of all training plans.
		 * \param event The event data.
		 */
		void refreshTrainingPlanState(wxTimerEvent& event);
		/**
		 * \brief Converts the given duration to a readable string.
		 * \param duration The duration.
		 * \return The string.
		 */
		std::string getStringFromDuration(std::chrono::duration<double> duration) const;
		/**
		 * \brief Returns the corresponding controller.
		 * \return The controller.
		 */
		TrainingController& getController();
	protected:
		/**
		 * \brief Is called when the window should be closed.
		 * \param event The event data.
		 */
		void close(wxCloseEvent& event);
		DECLARE_EVENT_TABLE();
	public:
		/**
		 * \brief Creates the training window.
		 * \param controller_ The corresponding controller.
		 */
		TrainingWindow(TrainingController& controller_);
		/**
		 * \brief Adds a new sub app factory.
		 * \param newSubAppFactory The new sub app factory.
		 */
		void addSubAppFactory(AbstractSubAppFactory& newSubAppFactory);
	};
}

#endif
