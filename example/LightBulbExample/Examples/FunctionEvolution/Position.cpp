// Includes
#include "Examples/FunctionEvolution/Position.hpp"
#include "Examples/FunctionEvolution/FunctionSimulator.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

using namespace LightBulb;

Position::Position(FunctionSimulator& functionSimulator_)
	: AbstractDefaultIndividual(functionSimulator_)
{
	functionSimulator = &functionSimulator_;

	FeedForwardNetworkTopologyOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(2);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
	inputIsSet = false;
}

void Position::getNNInput(LightBulb::Vector<>& input)
{
	if (!inputIsSet) {
		input.getEigenValueForEditing()[0] = 1;
		inputIsSet = true;
	}
}

void Position::interpretNNOutput(const LightBulb::Vector<>& output)
{
	position = output;
}

const LightBulb::Vector<>& Position::getPosition() const
{
	return position;
}

Position::~Position()
{
}

