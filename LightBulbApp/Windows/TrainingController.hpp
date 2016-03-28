#pragma once

#ifndef _TRAININGCONTROLLER_H_
#define _TRAININGCONTROLLER_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include <Logging/AbstractLogger.hpp>

// Forward declarations
class TrainingWindow;

class TrainingController
{
private:
	std::vector<AbstractNeuralNetwork*> neuralNetworks;
	std::vector<AbstractTrainingPlan*> trainingPlanPatterns;
	std::vector<AbstractTrainingPlan*> trainingPlans;
	std::unique_ptr<TrainingWindow> window;
	AbstractLogger* logger;
public:
	TrainingController();
	std::vector<AbstractNeuralNetwork*>* getNeuralNetworks();
	std::vector<AbstractTrainingPlan*>* getTrainingPlanPatterns();
	std::vector<AbstractTrainingPlan*>* getTrainingPlans();
	void startTrainingPlanPattern(int trainingPlanPatternIndex, int neuralNetworkIndex);
	void pauseTrainingPlan(AbstractTrainingPlan* trainingPlan);
	int getIndexOfNeuralNetwork(AbstractNeuralNetwork* network);
	int getIndexOfTrainingPlanPattern(AbstractTrainingPlan* trainingPlanPattern);
	void trainingPlanPaused(AbstractTrainingPlan* trainingPlan);
	void trainingPlanFinished(AbstractTrainingPlan* trainingPlan);
	void resumeTrainingPlan(AbstractTrainingPlan* trainingPlan);
	void setLogger(AbstractLogger* newLogger);
	void show();
};

#endif
