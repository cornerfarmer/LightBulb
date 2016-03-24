// Includes
#include "Graphics/TrainingController.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/ExampleTrainingPlan.hpp>
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/FermiFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include "TrainingWindow.hpp"

TrainingController::TrainingController(TrainingWindow* window_)
{
	window = window_;

	LayeredNetworkOptions options;
	options.neuronsPerLayerCount.push_back(4);
	options.neuronsPerLayerCount.push_back(7);
	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(10);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	neuralNetworks.push_back(new NeuralNetwork(new LayeredNetwork(options)));

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
	trainingPlans.back()->start(neuralNetworks[neuralNetworkIndex]);
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

int TrainingController::getIndexOfNeuralNetwork(AbstractNeuralNetwork* network)
{
	for (int i = 0; i < neuralNetworks.size(); i++)
	{
		if (neuralNetworks[i] == network)
			return i;
	}
	return -1;
}
