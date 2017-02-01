// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
// Library includes
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	void AbstractIndividual::randomizeMutationStrength()
	{
		// Go through all mutation strength values
		for (int i = 0; i < mutationStrength.getEigenValue().size(); i++)
		{
			// Set it to a random value
			mutationStrength.getEigenValueForEditing()(i) = 0.2; // (float)rand() / RAND_MAX * 0.1;
		}
	}

	void AbstractIndividual::copyPropertiesFrom(AbstractIndividual& notUsedIndividual)
	{
		getNeuralNetwork().getNetworkTopology().copyWeightsFrom(notUsedIndividual.getNeuralNetwork().getNetworkTopology());
		setMutationStrength(notUsedIndividual.getMutationStrength());
	}

	Vector<>& AbstractIndividual::getMutationStrength()
	{
		return mutationStrength;
	}

	const Vector<>& AbstractIndividual::getMutationStrength() const
	{
		return mutationStrength;
	}

	void AbstractIndividual::setMutationStrength(const Vector<>& newMutationStrength)
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
		mutationStrength.getEigenValueForEditing().resize(getNeuralNetwork().getNetworkTopology().getEdgeCount());
	}

	void AbstractIndividual::addNeuron(int layerIndex)
	{
		getNeuralNetwork().getNetworkTopology().addNeuron(layerIndex);
		// TODO: Set new values to 0.2
		mutationStrength.getEigenValueForEditing().resize(getNeuralNetwork().getNetworkTopology().getEdgeCount());
	}

	void AbstractIndividual::setCalculatorType(const CalculatorType& calculatorType)
	{
		getNeuralNetwork().getNetworkTopology().setCalculatorType(calculatorType);
	}

	void AbstractIndividual::resizeMutationStrength(int newSize)
	{
		mutationStrength.getEigenValueForEditing().resize(newSize);
	}
}