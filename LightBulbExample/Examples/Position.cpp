// Includes
#include "Examples/Position.hpp"
#include "Examples/FunctionSimulator.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Function/ActivationFunction/IdentityFunction.hpp>
#include <Neuron/NeuronDescription.hpp>


Position::Position(FunctionSimulator* functionSimulator_)
	: AbstractSimpleEvolutionObject(functionSimulator_)
{
	functionSimulator = functionSimulator_;
	position.resize(2);

	LayeredNetworkOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(2);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
}

void Position::getNNInput(std::vector<double>& input)
{
	input.resize(1);
	input[0] = 1;
}

void Position::interpretNNOutput(std::vector<double>& output)
{
	for (int i = 0; i < 2; i++)
	{	
		position[i] = output[i];
	}
}

std::vector<float> Position::getPosition()
{
	return position;
}

Position::~Position()
{
}

