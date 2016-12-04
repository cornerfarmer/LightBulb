// Includes
#include "LightBulb/Learning/Evolution/NetworkGrowMutationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	NetworkGrowMutationAlgorithm::NetworkGrowMutationAlgorithm(const std::vector<unsigned int>& maxNeuronsPerLayer_)
	{
		maxNeuronsPerLayer = maxNeuronsPerLayer_;
	}

	void NetworkGrowMutationAlgorithm::execute(AbstractIndividual& individual1)
	{
		AbstractNetworkTopology& networkTopology = individual1.getNeuralNetwork().getNetworkTopology();
		const std::vector<unsigned>& neuronCountsPerLayer = networkTopology.getNeuronCountsPerLayer();

		bool addingNeuronsPossible = false;
		for (int l = 0; l < neuronCountsPerLayer.size(); l++)
		{
			if (maxNeuronsPerLayer[l] > neuronCountsPerLayer[l])
			{
				addingNeuronsPossible = true;
				break;
			}
		}

		if (addingNeuronsPossible)
		{
			int layer;
			do
			{
				layer = randomGenerator->randInt(0, neuronCountsPerLayer.size() - 1);
			} while (maxNeuronsPerLayer[layer] <= neuronCountsPerLayer[layer]);
			individual1.addNeuron(layer);
		}

	}

	AbstractCloneable* NetworkGrowMutationAlgorithm::clone() const
	{
		return new NetworkGrowMutationAlgorithm(*this);
	}
}
