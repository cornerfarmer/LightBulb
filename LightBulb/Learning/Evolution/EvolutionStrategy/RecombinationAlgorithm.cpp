// Includes
#include "Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/FastLayeredNetwork.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"

RecombinationAlgorithm::RecombinationAlgorithm(bool useAverageForWeight_, bool useAverageForMutationStrength_)
{
	useAverageForWeight = useAverageForWeight_;
	useAverageForMutationStrength = useAverageForMutationStrength_;
}

void RecombinationAlgorithm::execute(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2)
{
	auto weights1 = static_cast<FastLayeredNetwork*>(object1->getNeuralNetwork()->getNetworkTopology())->getWeights();
	auto weights2 = static_cast<FastLayeredNetwork*>(object2->getNeuralNetwork()->getNetworkTopology())->getWeights();
	// Go through all edges
	auto neuron2 = weights2->begin();
	for (auto neuron1 = weights1->begin(); neuron1 != weights1->end(); neuron1++, neuron2++)
	{
		auto weight2 = neuron2->begin();
		for (auto weight1 = neuron1->begin(); weight1 != neuron1->end(); weight1++, weight2++)
		{
			if (useAverageForWeight)
			{
				// Calculate the weights average and store it inside the first object
				*weight1 = (*weight1 + *weight2) / 2;
			}
			else
			{
				if (rand() > RAND_MAX / 2)
					*weight1 = *weight2;
			}
		}
	}


	auto mutationStrength2 = object2->getMutationStrength()->begin();
	for (auto mutationStrength1 = object1->getMutationStrength()->begin(); mutationStrength1 != object1->getMutationStrength()->end() && mutationStrength2 != object2->getMutationStrength()->end(); mutationStrength1++, mutationStrength2++)
	{
		if (useAverageForMutationStrength)
		{
			*mutationStrength1 = (*mutationStrength2 + *mutationStrength1) / 2;
		}
		else
		{
			if (rand() > RAND_MAX / 2)
				*mutationStrength1 = *mutationStrength2;
		}
	}
}
