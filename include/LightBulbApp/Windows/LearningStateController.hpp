#pragma once

#ifndef _LEARNINGSTATECONTROLLER_H_
#define _LEARNINGSTATECONTROLLER_H_

// Library includes
#include <vector>
#include <map>

// Includes
#include "LearningStateWindow.hpp"
#include "AbstractSubApp.hpp"
#include "LightBulb/Learning/LearningState.hpp"

#define DEFAULT_COMP_DS "Iterations"

namespace LightBulb
{
	// Forward declarations
	class TrainingWindow;
	class TrainingController;
	class TrainingPlanRepository;
	class AbstractTrainingPlan;

	/**
	 * \brief Describes a selected data set in the LearningStateController.
	 */
	struct DataSetSelection
	{
		/**
		 * \brief The training plan which contains the data set.
		 */
		AbstractTrainingPlan* trainingPlan;
		/**
		 * \brief The number of the try which contains the data set.
		 */
		int tryNumber;
		/**
		 * \brief The label of the dataset.
		 */
		std::string label;
		/**
		 * \brief Returns the dataset.
		 * \param otherLabel Can be set to obtain another dataset from the same try.
		 * \return The data set.
		 */
		DataSet& getDataSet(std::string otherLabel = "");
	};

	/**
	 * \brief A sub app which visualizes the current state of learning rules.
	 */
	class LearningStateController : public AbstractSubApp
	{
	private:
		/**
		 * \brief The corresponding window.
		 */
		LearningStateWindow* window;
		/**
		 * \brief The training plan repository to get all current training plans.
		 */
		TrainingPlanRepository* trainingPlanRepository;
		/**
		 * \brief The currently selected training plan.
		 */
		AbstractTrainingPlan* selectedTrainingPlan;
		/**
		 * \brief The currently selected data set.
		 */
		std::vector<DataSetSelection> selectedDataSets;
		/**
		 * \brief Iterations since the last refresh.
		 */
		int iterationsSinceLearningStateChanged;
		/**
		 * \brief After how many iterations the graph should refresh.
		 */
		int refreshRate;
		/**
		 * \brief True if a refresh is already scheduled.
		 */
		bool refreshScheduled;
		/**
		 * \brief The label of the current comparison data set.
		 */
		std::string comparisonDataSetLabel;
	protected:
		// Inherited:
		void prepareClose() override;
	public:
		/**
		 * \brief Creates the learning state controller.
		 * \param mainApp The main app which should manage the sub app.
		 * \param trainingPlanRepository_ The training plan repository.
		 * \param parent The parent window.
		 */
		LearningStateController(AbstractMainApp& mainApp, TrainingPlanRepository& trainingPlanRepository_, AbstractWindow& parent);
		/**
		 * \brief Returns the corresponding window.
		 * \return The window.
		 */
		LearningStateWindow& getWindow();
		/**
		 * \brief Returns all current training plans.
		 * \return A vector of all training plans.
		 */
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>& getTrainingPlans() const;
		/**
		 * \brief Is called when the training plan repository has been changed.
		 * \param trainingPlanRepository The training plan repository.
		 */
		void trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository);
		/**
		 * \brief Sets the index of the currently selected training plan.
		 * \param trainingPlanIndex The index of the training plan to select.
		 */
		void setSelectedTrainingPlan(int trainingPlanIndex);
		/**
		 * \brief Returns the currently selected training plan.
		 * \return The training plan.
		 */
		AbstractTrainingPlan& getSelectedTrainingPlan();
		/**
		 * \brief Is called when the learning state has changed.
		 * \param learningState The learning state.
		 */
		void learningStateChanged(LearningState& learningState);
		/**
		 * \brief Sets the refresh rate.
		 * \details Determines after how many iterations the graph should refresh.
		 * \param newRefreshRate The new refresh rate.
		 */
		void setRefreshRate(int newRefreshRate);
		/**
		 * \brief Returns the current refresh rate.
		 * \return The refresh rate.
		 */
		int getRefreshRate();
		/**
		 * \brief Is called after a refresh has finished.
		 */
		void refreshFinished();
		/**
		 * \brief Returns all data set labels of the currently selected training plan.
		 * \return A vector of all labels.
		 */
		std::vector<std::string> getDataSetLabels();
		/**
		 * \brief Returns the amount of tries in the currently selected trianing plan.
		 * \return The amount of tries.
		 */
		int getTryCount();
		/**
		 * \brief Adds a new data set of the currently selected trianing plan to the visualization.
		 * \param tryNumber The number of the try.
		 * \param dataSetIndex The index of the data set.
		 * \return The label of the added data set.
		 */
		std::string addDataSet(int tryNumber, int dataSetIndex);
		/**
		 * \brief Returns all selected data sets.
		 * \return A vector with all data set selections.
		 */
		std::vector<DataSetSelection>& getSelectedDataSets();
		/**
		 * \brief Removes the dataset with the given index from the selection.
		 * \param dataSetIndex The index of the dataset to remove.
		 */
		void removeDataSet(int dataSetIndex);
		/**
		 * \brief Returns the label of the current comparison data set.
		 * \return The label.
		 */
		const std::string& getComparisonDataSetLabel() const;
		/**
		 * \brief Sets the comparison data set.
		 * \param newComparisonDataSetLabel The label of the new comparison data set.
		 */
		void setComparisonDataSetLabel(std::string newComparisonDataSetLabel);
		/**
		 * \brief Returns the label of the dataset.
		 * \return The label.
		 */
		static std::string getLabel();
		/**
		 * \brief Returns all data set labels which can be used as a comparison dataset.
		 * \return A vecor of all labels.
		 */
		std::vector<std::string> getPossibleComparisonDatasetLabels();
	};
}

#endif
