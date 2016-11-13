#pragma once

#ifndef _TRAININGCONTROLLER_H_
#define _TRAININGCONTROLLER_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include <Logging/AbstractLogger.hpp>
#include "LoggerController.hpp"
#include "TrainingWindow.hpp"
#include "AbstractMainApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetworkRepository;
	class TrainingPlanRepository;
	class AbstractSubAppFactory;

	/**
	 * \brief The main app which manages all neural networks an training plans.
	 * \details The app lists all networks and training plans, shows detail information and adds the possibility to start, pause, save and load training plans.
	 */
	class TrainingController : public AbstractMainApp
	{
		template <class Archive>
		friend void serialize(Archive& archive, TrainingController& trainingController);
	private:
		/**
		 * \brief Contains all available training plan patterns.
		 */
		std::vector<std::unique_ptr<AbstractTrainingPlan>> trainingPlanPatterns;
		/**
		 * \brief The corresponding window.
		 */
		TrainingWindow* window;
		/**
		 * \brief Contains all currently running sub apps.
		 */
		std::vector<std::unique_ptr<AbstractSubApp>> activeSubApps;
		/**
		 * \brief All available sub app factories.
		 */
		std::vector<AbstractSubAppFactory*> subAppFactories;
		/**
		 * \brief The network repository which provides access to all existing networks.
		 */
		NeuralNetworkRepository* neuralNetworkRepository;
		/**
		* \brief The training plan repository which provides access to all existing training plans.
		*/
		TrainingPlanRepository* trainingPlanRepository;
		/**
		 * \brief Saves the training plan with this index after it has been paused.
		 */
		int saveTrainingPlanAfterPausedIndex;
		/**
		 * \brief True, if the whole training session should be saved after all training plans has been paused.
		 */
		bool saveTrainingSessionAfterPause;
		/**
		* \brief True, if the window should be closed after pausing.
		*/
		bool closeWindowAfterPause;
		/**
		 * \brief Returns if all current training plans are paused.
		 * \return True, if they are paused.
		 */
		bool allTrainingPlansPaused();
	public:
		/**
		 * \brief Creates the training app.
		 * \param neuralNetworkRepository_ The neural network repository to use.
		 * \param trainingPlanRepository_ The training plan repository to use.
		 * \param trainingPlanPatterns_ All available training plans.
		 */
		TrainingController(NeuralNetworkRepository& neuralNetworkRepository_, TrainingPlanRepository& trainingPlanRepository_, std::vector<AbstractTrainingPlan*>& trainingPlanPatterns_);
		/**
		 * \brief Returns all current neural networks.
		 * \return A vector of neural networks.
		 */
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& getNeuralNetworks() const;
		/**
		 * \brief Returns all training plan patterns.
		 * \return A vector of training plans.
		 */
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>& getTrainingPlanPatterns() const;
		/**
		 * \brief Returns all running training plans.
		 * \return A vector of training plans.
		 */
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>& getTrainingPlans() const;
		/**
		 * \brief Starts the training plan with the given index together with the neural network with the given index.
		 * \param trainingPlanPatternIndex The index of the training plan to start.
		 * \note The neural network index will only be used if the training plan is a AbstractSingleNNTrainingPlan.
		 */
		void startTrainingPlanPattern(int trainingPlanPatternIndex);
		/**
		 * \brief Is called after the neural network repository has been changed.
		 * \param neuralNetworkRepository The neural network repository.
		 */
		void neuralNetworksChanged(NeuralNetworkRepository& neuralNetworkRepository);
		/**
		 * \brief Is called after the training plan repository has been changed.
		 * \param trainingPlanRepository The training plan repository.
		 */
		void trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository);
		/**
		 * \brief Pauses the given training plan.
		 * \param trainingPlan The training plan to pause.
		 */
		void pauseTrainingPlan(AbstractTrainingPlan& trainingPlan);
		/**
		 * \brief Returns the index of the given network in the storage of the network repository.
		 * \param network The network.
		 * \return The index of the network.
		 */
		int getIndexOfNeuralNetwork(const AbstractNeuralNetwork& network) const;
		/**
		* \brief Returns the index of the training plan pattern with the given name in the internal storage.
		* \param name The name of the training plan pattern.
		* \return The index of the training plan pattern.
		*/
		int getIndexOfTrainingPlanPatternWithName(const std::string& name) const;
		/**
		 * \brief Is called after a training plan has been paused.
		 * \param trainingPlan The training plan which has been paused.
		 */
		void trainingPlanPaused(AbstractTrainingPlan& trainingPlan);
		/**
		 * \brief Is called after a training plan has been finished.
		 * \param trainingPlan The training plan which has been finished.
		 */
		void trainingPlanFinished(AbstractTrainingPlan& trainingPlan);
		/**
		 * \brief Resumes the given training plan.
		 * \param trainingPlan The training plan to resume.
		 */
		void resumeTrainingPlan(AbstractTrainingPlan& trainingPlan);
		/**
		 * \brief Shows the window.
		 */
		void show();
		/**
		 * \brief Returns the corresponding window.
		 * \return The window.
		 */
		TrainingWindow& getWindow();
		/**
		 * \brief Adds a new sub app factory to the main app.
		 * \param newSubAppFactory The new sub app factory.
		 */
		void addSubAppFactory(AbstractSubAppFactory* newSubAppFactory);
		/**
		 * \brief Saves the network with the given index to the file with the given path.
		 * \param path The path of the file which should be created.
		 * \param neuralNetworkIndex The index of the network which should be saved.
		 */
		void saveNeuralNetwork(const std::string& path, int neuralNetworkIndex);
		/**
		 * \brief Loads a network from a file with the given path.
		 * \param path The path of the file which should be loaded.
		 */
		void loadNeuralNetwork(const std::string& path);
		/**
		 * \brief Initializes saving of the training plan with the given index.
		 * \details If necessary, the training plan will be paused. After that the save dialog will show up.
		 * \param trainingPlanIndex The index of the training plan to save.
		 */
		void saveTrainingPlan(int trainingPlanIndex);
		/**
		 * \brief Saves the training plan with the given index to the file with the given path
		 * \param path The path of the file which should be created.
		 * \param trainingPlanIndex The index of the training plan which should be saved.
		 */
		void saveTrainingPlan(const std::string& path, int trainingPlanIndex);
		/**
		 * \brief Loads a training plan from a file with the given path.
		 * \param path The path of the file which should be loaded.
		 */
		void loadTrainingPlan(const std::string& path);
		/**
		 * \brief Loads the training session from a file with the given path.
		 * \param path The path of the file which should be loaded.
		 */
		void loadTrainingSession(const std::string& path);
		/**
		 * \brief Saves the whole training session to a file with the given path.
		 * \param path The path of the file which should be created.
		 */
		void saveTrainingSession(const std::string& path);
		/**
		 * \brief 
		 * \return 
		 */
		bool closeWindow();
		/**
		 * \brief Initializes saving of the whole training session.
		 * \details If necessary, all training plans will be paused. After that the save dialog will show up.
		 */
		void saveTrainingSession();
		/**
		 * \brief Creates and adds a sub app from the factory with the given index.
		 * \param subAppFactoryIndex The index of the sub app factory which should be used.
		 */
		void addSubApp(int subAppFactoryIndex);
		/**
		 * \brief Shows the preferences sub app for the training plan pattern with the given index.
		 * \param trainingPlanPatternIndex The index of the training plan whose preferences should be shown.
		 */
		void openPreferences(int trainingPlanPatternIndex);
		/**
		 * \brief Sets the name of the training plan with the given index.
		 * \param trainingPlanIndex The index of the training plan.
		 * \param newName The new name.
		 */
		void setTrainingPlanName(int trainingPlanIndex, const std::string& newName);
		/**
		 * \brief Removes the given sub app from the internal storage.
		 * \param subApp The sub app to remove.
		 */
		void removeSubApp(const AbstractSubApp& subApp) override;
	};
}

#include "IO/TrainingControllerIO.hpp"

#endif
