// Includes
#include "LightBulb/Learning/Evolution/AbstractDefaultIndividual.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"

namespace LightBulb
{
	void AbstractDefaultIndividual::buildNeuralNetwork(FeedForwardNetworkTopologyOptions& options)
	{
		// Create a new network topology from the adjusted options.
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

		// Create a neural network from the network topolgy
		neuralNetwork.reset(new NeuralNetwork(networkTopology));
		// Randomize all weights
		neuralNetwork->getNetworkTopology().randomizeDependingOnLayerSize(environment->getRandomGenerator());

		lastInput.getEigenValueForEditing().resize(networkTopology->getInputSize() + networkTopology->usesBiasNeuron());
		if (networkTopology->usesBiasNeuron())
			lastInput.getEigenValueForEditing()[networkTopology->getInputSize()] = 1;

		// Initialize the mutation strength vector
		resizeMutationStrength(neuralNetwork->getNetworkTopology().getEdgeCount());
		randomizeMutationStrength();
	}

	AbstractDefaultIndividual::AbstractDefaultIndividual(AbstractEvolutionEnvironment& environment_)
	{
		environment = &environment_;
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
		const Vector<>& output = neuralNetwork->calculateWithoutOutputCopy(lastInput, topologicalOrder, false);

		// Interpret the output
		interpretNNOutput(output);
	}


	void AbstractDefaultIndividual::resetNN()
	{
		// Only reset all activations
		neuralNetwork->getNetworkTopology().resetActivation();
	}

	AbstractIndividual* AbstractDefaultIndividual::clone(bool addToEnvironment) const
	{
		// Create a new individual
		AbstractIndividual* newIndividual = environment->addNewIndividual(addToEnvironment);
		// Copy all weights
		newIndividual->getNeuralNetwork().getNetworkTopology().copyWeightsFrom(neuralNetwork->getNetworkTopology());
		// Copy all mutation strengths
		newIndividual->setMutationStrength(getMutationStrength());
		return newIndividual;
	}
}