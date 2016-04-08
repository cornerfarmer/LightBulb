// Includes
#include "TrainingPlans/ExampleTrainingPlan.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/FermiFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <Learning/LearningState.hpp>

void ExampleTrainingPlan::run(bool initial)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		if (shouldPause)
			break;
	}
	shouldPause = false;
	pausingFinished();
}

AbstractNeuralNetwork* ExampleTrainingPlan::createNeuralNetwork()
{
	LayeredNetworkOptions options;
	options.neuronsPerLayerCount.push_back(4);
	options.neuronsPerLayerCount.push_back(7);
	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(10);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	return new NeuralNetwork(new LayeredNetwork(options));
}

void ExampleTrainingPlan::tryToPause()
{
	shouldPause = true;
}

std::string ExampleTrainingPlan::getName()
{
	return "ExampleTrainingPlan";
}

std::string ExampleTrainingPlan::getDescription()
{
	return "Bla bla bla!";
}

std::string ExampleTrainingPlan::getLearningRuleName()
{
	return "Backpropagation";
}

AbstractTrainingPlan* ExampleTrainingPlan::getCopy()
{
	return new ExampleTrainingPlan();
}

int ExampleTrainingPlan::getRequiredInputSize()
{
	return 3;
}

int ExampleTrainingPlan::getRequiredOutputSize()
{
	return 6;
}

std::vector<std::string> ExampleTrainingPlan::getDataSetLabels()
{
	return std::vector<std::string>();
}

LearningState* ExampleTrainingPlan::getLearningState()
{
	return new LearningState();
}
