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

class TrainingController
{
private:
	std::vector<AbstractTrainingPlan*> trainingPlanPatterns;
	std::vector<AbstractTrainingPlan*> trainingPlans;
	std::unique_ptr<TrainingWindow> window;
	AbstractLogger* logger;
	NeuralNetworkRepository* neuralNetworkRepository;
public:
	TrainingController(NeuralNetworkRepository* neuralNetworkRepository_);
	std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks();
	std::vector<AbstractTrainingPlan*>* getTrainingPlanPatterns();
	std::vector<AbstractTrainingPlan*>* getTrainingPlans();
	void startTrainingPlanPattern(int trainingPlanPatternIndex, int neuralNetworkIndex);
	void neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository);
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
};

#endif
