// Includes
#include "Graphics/TrainingController.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/ExampleTrainingPlan.hpp>
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/FermiFunction.hpp>
#include <Neuron/NeuronDescription.hpp>

TrainingController::TrainingController()
{
	LayeredNetworkOptions options;
	options.neuronsPerLayerCount.push_back(4);
	options.neuronsPerLayerCount.push_back(7);
	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(10);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	neuralNetworks.push_back(new NeuralNetwork(new LayeredNetwork(options)));

	trainingPlanPatterns.push_back(new ExampleTrainingPlan());
	trainingPlanPatterns.push_back(new ExampleTrainingPlan());

	trainingPlans.push_back(new ExampleTrainingPlan());
	trainingPlans[0]->start(neuralNetworks[0]);
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
