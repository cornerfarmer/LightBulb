// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "AbstractEvolutionWorld.hpp"

namespace LightBulb
{
	void AbstractSimpleEvolutionObject::buildNeuralNetwork(FeedForwardNetworkTopologyOptions& options)
	{
		// Create a new network topology from the adjusted options.
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

		// Create a neural network from the network topolgy
		neuralNetwork.reset(new NeuralNetwork(networkTopology));
		// Randomize all weights (TODO: make the boundaries variable)
		neuralNetwork->getNetworkTopology().randomizeWeights(world->getRandomGenerator(), -0.5, 0.5);

		// Initialize the mutation strength vector
		resizeMutationStrength(neuralNetwork->getNetworkTopology().getEdgeCount());
		randomizeMutationStrength();
		buildOutputBuffer();
	}

	void AbstractSimpleEvolutionObject::buildOutputBuffer()
	{
		lastOutput.resize(neuralNetwork->getNetworkTopology().getOutputSize());
	}

	AbstractSimpleEvolutionObject::AbstractSimpleEvolutionObject(AbstractEvolutionWorld& world_)
	{
		world = &world_;
	}

	AbstractNeuralNetwork* AbstractSimpleEvolutionObject::getNeuralNetwork()
	{
		return neuralNetwork.get();
	}

	void AbstractSimpleEvolutionObject::doNNCalculation()
	{
		// Get the input
		getNNInput(lastInput);

		TopologicalOrder topologicalOrder;
		// Calculate the output from the the input
		neuralNetwork->calculate(lastInput, lastOutput, topologicalOrder, false);

		// Interpret the output
		interpretNNOutput(lastOutput);
	}


	void AbstractSimpleEvolutionObject::resetNN()
	{
		// Only reset all activations
		neuralNetwork->getNetworkTopology().resetActivation();
	}

	AbstractEvolutionObject* AbstractSimpleEvolutionObject::clone(bool addToWorld)
	{
		// Create a new object
		AbstractEvolutionObject* newObject = world->addNewObject(addToWorld);
		// Copy all weights
		newObject->getNeuralNetwork()->getNetworkTopology().copyWeightsFrom(neuralNetwork->getNetworkTopology());
		// Copy all mutation strengths
		newObject->setMutationStrength(getMutationStrength());
		return newObject;
	}
}