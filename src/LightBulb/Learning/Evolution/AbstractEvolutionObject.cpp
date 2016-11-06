// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
// Library includes
#include <stdlib.h>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

namespace LightBulb
{
	void AbstractEvolutionObject::randomizeMutationStrength()
	{
		// Go through all mutation strength values
		for (auto mutationStrengthValue = mutationStrength.begin(); mutationStrengthValue != mutationStrength.end(); mutationStrengthValue++)
		{
			// Set it to a random value
			*mutationStrengthValue = 0.2; // (float)rand() / RAND_MAX * 0.1;
		}
	}

	void AbstractEvolutionObject::copyPropertiesFrom(AbstractEvolutionObject& notUsedObject)
	{
		getNeuralNetwork().getNetworkTopology().copyWeightsFrom(notUsedObject.getNeuralNetwork().getNetworkTopology());
		setMutationStrength(notUsedObject.getMutationStrength());
	}

	std::vector<double>& AbstractEvolutionObject::getMutationStrength()
	{
		return mutationStrength;
	}

	const std::vector<double>& AbstractEvolutionObject::getMutationStrength() const
	{
		return mutationStrength;
	}

	void AbstractEvolutionObject::setMutationStrength(const std::vector<double>& newMutationStrength)
	{
		mutationStrength = newMutationStrength;
	}

	void AbstractEvolutionObject::setEvolutionSource(const EvolutionSource& evolutionSource_)
	{
		evolutionSource = evolutionSource_;
	}

	const EvolutionSource& AbstractEvolutionObject::getEvolutionSource() const
	{
		return evolutionSource;
	}

	void AbstractEvolutionObject::removeNeuron(int layerIndex, int neuronIndex)
	{
		getNeuralNetwork().getNetworkTopology().removeNeuron(layerIndex, neuronIndex);
		mutationStrength.resize(getNeuralNetwork().getNetworkTopology().getEdgeCount());
	}

	void AbstractEvolutionObject::addNeuron(int layerIndex)
	{
		getNeuralNetwork().getNetworkTopology().addNeuron(layerIndex);
		mutationStrength.resize(getNeuralNetwork().getNetworkTopology().getEdgeCount(), 0.2);
	}

	void AbstractEvolutionObject::resizeMutationStrength(int newSize)
	{
		mutationStrength.resize(newSize);
	}
}