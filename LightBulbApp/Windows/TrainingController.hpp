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

// Forward declarations
class NeuralNetworkRepository;
class TrainingPlanRepository;

class TrainingController
{
	template <class Archive>
	friend void serialize(Archive& archive, TrainingController& trainingController);
private:
	std::vector<AbstractTrainingPlan*> trainingPlanPatterns;
	std::unique_ptr<TrainingWindow> window;
	AbstractLogger* logger;
	NeuralNetworkRepository* neuralNetworkRepository;
	TrainingPlanRepository* trainingPlanRepository;
	int saveTrainingPlanAfterPausedIndex;
public:
	TrainingController(NeuralNetworkRepository* neuralNetworkRepository_, TrainingPlanRepository* trainingPlanRepository_);
	std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks();
	std::vector<AbstractTrainingPlan*>* getTrainingPlanPatterns();
	std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans();
	void startTrainingPlanPattern(int trainingPlanPatternIndex, int neuralNetworkIndex);
	void neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository);
	void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
	void pauseTrainingPlan(AbstractTrainingPlan* trainingPlan);
	int getIndexOfNeuralNetwork(AbstractNeuralNetwork* network);
	int getIndexOfTrainingPlanPattern(AbstractTrainingPlan* trainingPlanPattern);
	void trainingPlanPaused(AbstractTrainingPlan* trainingPlan);
	void trainingPlanFinished(AbstractTrainingPlan* trainingPlan);
	void resumeTrainingPlan(AbstractTrainingPlan* trainingPlan);
	void setLogger(AbstractLogger* newLogger);
	void show();
	TrainingWindow* getWindow();
	void addSubWindow(AbstractWindow* newSubWindow);
	void saveNeuralNetwork(std::string path, int neuralNetworkIndex);
	void loadNeuralNetwork(std::string path);
	void saveTrainingPlan(int trainingPlanIndex);
	void saveTrainingPlan(std::string path, int trainingPlanIndex);
	void loadTrainingPlan(std::string path);
	void loadTrainingSession(std::string path);
	void saveTrainingSession(std::string path);
};

#endif
