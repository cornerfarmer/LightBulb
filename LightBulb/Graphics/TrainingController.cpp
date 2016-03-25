// Includes
#include "Graphics/TrainingController.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/ExampleTrainingPlan.hpp>

#include "TrainingWindow.hpp"

TrainingController::TrainingController(TrainingWindow* window_)
{
	window = window_;

	trainingPlanPatterns.push_back(new ExampleTrainingPlan());
	trainingPlanPatterns.push_back(new ExampleTrainingPlan());
}

std::vector<AbstractNeuralNetwork*>* TrainingController::getNeuralNetworks()
{
	return &neuralNetworks;
}

std::vector<AbstractTrainingPlan*>* TrainingController::getTrainingPlanPatterns()
{
	return &trainingPlanPatterns;
}

std::vector<AbstractTrainingPlan*>* TrainingController::getTrainingPlans()
{
	return &trainingPlans;
}

void TrainingController::startTrainingPlanPattern(int trainingPlanPatternIndex, int neuralNetworkIndex)
{
	trainingPlans.push_back(trainingPlanPatterns[trainingPlanPatternIndex]->getCopyForExecute());
	trainingPlans.back()->registerObserver(EVT_TP_PAUSED, &TrainingController::trainingPlanPaused, this);
	if (neuralNetworks.size() <= neuralNetworkIndex) 
	{
		trainingPlans.back()->start();
		neuralNetworks.push_back(trainingPlans.back()->getNeuralNetwork());
		window->refreshNeuralNetworks();
	} 
	else
	{
		trainingPlans.back()->start(neuralNetworks[neuralNetworkIndex]);
	}
	window->refreshTrainingPlans();
}

void TrainingController::pauseTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	trainingPlan->pause();
	window->refreshTrainingPlans();
}

int TrainingController::getIndexOfTrainingPlanPattern(AbstractTrainingPlan* trainingPlanPattern)
{
	for (int i = 0; i < trainingPlanPatterns.size(); i++)
	{
		if (trainingPlanPatterns[i] == trainingPlanPattern)
			return i;
	}
	return -1;
}

void TrainingController::trainingPlanPaused(AbstractTrainingPlan* trainingPlan)
{
	window->refreshTrainingPlans();
}

void TrainingController::resumeTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	trainingPlan->start();
	window->refreshTrainingPlans();
}

int TrainingController::getIndexOfNeuralNetwork(AbstractNeuralNetwork* network)
{
	for (int i = 0; i < neuralNetworks.size(); i++)
	{
		if (neuralNetworks[i] == network)
			return i;
	}
	return -1;
}
