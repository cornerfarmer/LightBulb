// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "NetworkTopology/RecurrentLayeredNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "AbstractEvolutionWorld.hpp"

void AbstractSimpleEvolutionObject::buildNeuralNetwork(LayeredNetworkOptions& options)
{
	// Create a new network topology from the adjusted options.
	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);

	// Create a neural network from the network topolgy
	neuralNetwork.reset(new NeuralNetwork(layeredNetwork));
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

AbstractNeuralNetwork* AbstractSimpleEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork.get();
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
