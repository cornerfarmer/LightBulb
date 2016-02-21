// Includes
#include "Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"

RecombinationAlgorithm::RecombinationAlgorithm(bool useAverageForWeight_, bool useAverageForMutationStrength_)
{
	useAverageForWeight = useAverageForWeight_;
	useAverageForMutationStrength = useAverageForMutationStrength_;
}

void RecombinationAlgorithm::execute(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2)
{
	auto weights1 = static_cast<LayeredNetwork*>(object1->getNeuralNetwork()->getNetworkTopology())->getWeights();
	auto weights2 = static_cast<LayeredNetwork*>(object2->getNeuralNetwork()->getNetworkTopology())->getWeights();

	auto layer1 = weights1->begin();
	auto layer2 = weights2->begin();
	for (; layer1 != weights1->end(); layer1++, layer2++)
	{
		for (int i = 0; i < layer1->cols(); i++)
		{
			for (int j = 0; j < layer1->rows(); j++)
			{
				if (useAverageForWeight)
				{
					// Calculate the weights average and store it inside the first object
					(*layer1)(i, j) = ((*layer1)(i, j) + (*layer2)(i, j)) / 2;
				}
				else
				{
					if (rand() > RAND_MAX / 2)
						(*layer1)(i, j) = (*layer2)(i, j);
				}
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
