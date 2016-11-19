// Includes
#include "Learning/Evolution/AbstractDefaultIndividual.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "AbstractEvolutionWorld.hpp"

namespace LightBulb
{
	void AbstractDefaultIndividual::buildNeuralNetwork(FeedForwardNetworkTopologyOptions& options)
	{
		// Create a new network topology from the adjusted options.
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

		// Create a neural network from the network topolgy
		neuralNetwork.reset(new NeuralNetwork(networkTopology));
		// Randomize all weights
		neuralNetwork->getNetworkTopology().randomizeDependingOnLayerSize(world->getRandomGenerator());

		// Initialize the mutation strength vector
		resizeMutationStrength(neuralNetwork->getNetworkTopology().getEdgeCount());
		randomizeMutationStrength();
		buildOutputBuffer();
	}

	void AbstractDefaultIndividual::buildOutputBuffer()
	{
		lastOutput.resize(neuralNetwork->getNetworkTopology().getOutputSize());
	}

	AbstractDefaultIndividual::AbstractDefaultIndividual(AbstractEvolutionWorld& world_)
	{
		world = &world_;
	}

	AbstractNeuralNetwork& AbstractDefaultIndividual::getNeuralNetwork()
	{
		return *neuralNetwork.get();
	}

	void AbstractDefaultIndividual::doNNCalculation()
	{
		// Get the input
		getNNInput(lastInput);

		TopologicalOrder topologicalOrder;
		// Calculate the output from the the input
		neuralNetwork->calculate(lastInput, lastOutput, topologicalOrder, false);

		// Interpret the output
		interpretNNOutput(lastOutput);
	}


	void AbstractDefaultIndividual::resetNN()
	{
		// Only reset all activations
		neuralNetwork->getNetworkTopology().resetActivation();
	}

	AbstractIndividual* AbstractDefaultIndividual::clone(bool addToWorld) const
	{
		// Create a new individual
		AbstractIndividual* newIndividual = world->addNewIndividual(addToWorld);
		// Copy all weights
		newIndividual->getNeuralNetwork().getNetworkTopology().copyWeightsFrom(neuralNetwork->getNetworkTopology());
		// Copy all mutation strengths
		newIndividual->setMutationStrength(getMutationStrength());
		return newIndividual;
	}
}