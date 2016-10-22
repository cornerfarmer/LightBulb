// Includes
#include "Learning/Evolution/NetworkGrowMutationAlgorithm.hpp"
#include "AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

namespace LightBulb
{
	NetworkGrowMutationAlgorithm::NetworkGrowMutationAlgorithm(std::vector<unsigned int> maxNeuronsPerLayer_)
	{
		maxNeuronsPerLayer = maxNeuronsPerLayer_;
	}

	void NetworkGrowMutationAlgorithm::execute(AbstractEvolutionObject* object1)
	{
		AbstractNetworkTopology& networkTopology = object1->getNeuralNetwork()->getNetworkTopology();
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
			object1->addNeuron(layer);
		}

	}
}