// Includes
#include "Examples/FunctionEvolution/Position.hpp"
#include "Examples/FunctionEvolution/FunctionSimulator.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
#include <LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/Function/ActivationFunction/IdentityFunction.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>

using namespace LightBulb;

Position::Position(FunctionSimulator& functionSimulator_)
	: AbstractDefaultIndividual(functionSimulator_)
{
	functionSimulator = &functionSimulator_;
	position.resize(2);

	FeedForwardNetworkTopologyOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(2);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
}

void Position::getNNInput(LightBulb::Vector<>& input)
{
	input.getEigenValueForEditing().resize(1);
	input.getEigenValueForEditing()[0] = 1;
}

void Position::interpretNNOutput(const LightBulb::Vector<>& output)
{
	for (int i = 0; i < 2; i++)
	{	
		position[i] = output.getEigenValue()[i];
	}
}

std::vector<float> Position::getPosition() const
{
	return position;
}

Position::~Position()
{
}

