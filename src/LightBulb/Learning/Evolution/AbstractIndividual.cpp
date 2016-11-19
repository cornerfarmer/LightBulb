// Includes
#include "Learning/Evolution/AbstractIndividual.hpp"
// Library includes
#include <stdlib.h>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

namespace LightBulb
{
	void AbstractIndividual::randomizeMutationStrength()
	{
		// Go through all mutation strength values
		for (auto mutationStrengthValue = mutationStrength.begin(); mutationStrengthValue != mutationStrength.end(); mutationStrengthValue++)
		{
			// Set it to a random value
			*mutationStrengthValue = 0.2; // (float)rand() / RAND_MAX * 0.1;
		}
	}

	void AbstractIndividual::copyPropertiesFrom(AbstractIndividual& notUsedIndividual)
	{
		getNeuralNetwork().getNetworkTopology().copyWeightsFrom(notUsedIndividual.getNeuralNetwork().getNetworkTopology());
		setMutationStrength(notUsedIndividual.getMutationStrength());
	}

	std::vector<double>& AbstractIndividual::getMutationStrength()
	{
		return mutationStrength;
	}

	const std::vector<double>& AbstractIndividual::getMutationStrength() const
	{
		return mutationStrength;
	}

	void AbstractIndividual::setMutationStrength(const std::vector<double>& newMutationStrength)
	{
		mutationStrength = newMutationStrength;
	}

	void AbstractIndividual::setEvolutionSource(const EvolutionSource& evolutionSource_)
	{
		evolutionSource = evolutionSource_;
	}

	const EvolutionSource& AbstractIndividual::getEvolutionSource() const
	{
		return evolutionSource;
	}

	void AbstractIndividual::removeNeuron(int layerIndex, int neuronIndex)
	{
		getNeuralNetwork().getNetworkTopology().removeNeuron(layerIndex, neuronIndex);
		mutationStrength.resize(getNeuralNetwork().getNetworkTopology().getEdgeCount());
	}

	void AbstractIndividual::addNeuron(int layerIndex)
	{
		getNeuralNetwork().getNetworkTopology().addNeuron(layerIndex);
		mutationStrength.resize(getNeuralNetwork().getNetworkTopology().getEdgeCount(), 0.2);
	}

	void AbstractIndividual::resizeMutationStrength(int newSize)
	{
		mutationStrength.resize(newSize);
	}
}