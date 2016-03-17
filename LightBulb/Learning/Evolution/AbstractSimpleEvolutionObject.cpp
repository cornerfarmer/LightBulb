// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "NetworkTopology/RecurrentLayeredNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Examples/Nature.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NeuronFactory/SameNeuronDescriptionFactory.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/FermiFunction.hpp"
#include "Function/HyperbolicTangentFunction.hpp"
#include "Function/IdentityFunction.hpp"
#include "Function/BinaryFunction.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "Examples/AbstractTile.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include <Neuron/NeuronDescription.hpp>

void AbstractSimpleEvolutionObject::buildNeuralNetwork(LayeredNetworkOptions& options)
{
	// Create a new network topology from the adjusted options.
	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);

	// Create a neural network from the network topolgy
	neuralNetwork = new NeuralNetwork(layeredNetwork);
	// Randomize all weights (TODO: make the boundaries variable)
	neuralNetwork->getNetworkTopology()->randomizeWeights(-0.5, 0.5);

	// Initialize the mutation strength vector
	resizeMutationStrength(neuralNetwork->getNetworkTopology()->getEdgeCount());
	randomizeMutationStrength();
}

AbstractSimpleEvolutionObject::AbstractSimpleEvolutionObject(AbstractEvolutionWorld* world_)
{
	world = world_;
}

NeuralNetwork* AbstractSimpleEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork;
}

void AbstractSimpleEvolutionObject::doNNCalculation()
{
	// Get the input
	static std::vector<double> input;
	getNNInput(input);

	TopologicalOrder topologicalOrder;
	static std::vector<double> output(neuralNetwork->getNetworkTopology()->getOutputSize());
	// Calculate the output from the the input
	neuralNetwork->calculate(input, output, topologicalOrder, false);
	
	// Interpret the output
	interpretNNOutput(output);
}

AbstractSimpleEvolutionObject::~AbstractSimpleEvolutionObject()
{
	delete(neuralNetwork);
}


void AbstractSimpleEvolutionObject::resetNN()
{
	// Only reset all activations
	neuralNetwork->getNetworkTopology()->resetActivation();
}

AbstractEvolutionObject* AbstractSimpleEvolutionObject::clone(bool addToWorld)
{
	// Create a new object
	AbstractEvolutionObject* newObject = world->addNewObject(addToWorld);
	// Copy all weights
	newObject->getNeuralNetwork()->getNetworkTopology()->copyWeightsFrom(*neuralNetwork->getNetworkTopology());
	// Copy all mutation strengths
	newObject->setMutationStrength(getMutationStrength());
	return newObject;
}
