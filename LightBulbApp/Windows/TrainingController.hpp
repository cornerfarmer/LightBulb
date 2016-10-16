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

	class TrainingController : public AbstractMainApp
	{
		template <class Archive>
		friend void serialize(Archive& archive, TrainingController& trainingController);
	private:
		std::vector<std::unique_ptr<AbstractTrainingPlan>> trainingPlanPatterns;
		std::unique_ptr<TrainingWindow> window;
		std::vector<std::unique_ptr<AbstractSubApp>> activeSubApps;
		std::vector<AbstractSubAppFactory*> subAppFactories;
		NeuralNetworkRepository* neuralNetworkRepository;
		TrainingPlanRepository* trainingPlanRepository;
		int saveTrainingPlanAfterPausedIndex;
		bool saveTrainingSessionAfterPause;
		bool allTrainingPlansPaused();
	public:
		TrainingController(NeuralNetworkRepository* neuralNetworkRepository_, TrainingPlanRepository* trainingPlanRepository_, std::vector<AbstractTrainingPlan*>& trainingPlanPatterns_);
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks() const;
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlanPatterns() const;
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans() const;
		void startTrainingPlanPattern(int trainingPlanPatternIndex, int neuralNetworkIndex);
		void neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository);
		void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
		void pauseTrainingPlan(AbstractTrainingPlan* trainingPlan);
		int getIndexOfNeuralNetwork(const AbstractNeuralNetwork* network) const;
		int getIndexOfTrainingPlanPattern(const AbstractTrainingPlan* trainingPlanPattern) const;
		void trainingPlanPaused(AbstractTrainingPlan* trainingPlan);
		void trainingPlanFinished(AbstractTrainingPlan* trainingPlan);
		void resumeTrainingPlan(AbstractTrainingPlan* trainingPlan);
		void show();
		TrainingWindow* getWindow();
		void addSubAppFactory(AbstractSubAppFactory* newSubAppFactory);
		void saveNeuralNetwork(const std::string& path, int neuralNetworkIndex);
		void loadNeuralNetwork(const std::string& path);
		void saveTrainingPlan(int trainingPlanIndex);
		void saveTrainingPlan(const std::string& path, int trainingPlanIndex);
		void loadTrainingPlan(const std::string& path);
		void loadTrainingSession(const std::string& path);
		void saveTrainingSession(const std::string& path);
		void saveTrainingSession();
		void addSubApp(int subAppFactoryIndex);
		void openPreferences(int trainingPlanPatternIndex);
		void setTrainingPlanName(int trainingPlanIndex, const std::string& newName);
		void removeSubApp(const AbstractSubApp* subApp) override;
	};
}

#include "IO/TrainingControllerIO.hpp"

#endif
