// Includes
#include "Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/FastLayeredNetwork.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"
#include <math.h>


MutationAlgorithm::MutationAlgorithm(double mutationStrengthChangeSpeed_)
{
	// Initialize the normal distribution with mean 0 and variance 1
	distribution = std::normal_distribution<double>(0, 1);
	mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
	// Initialize the mutation strength boundaries (TODO: Make them variable)
	mutationStrengthMax = 50;
	mutationStrengthMin = 0.000001f;
}

void MutationAlgorithm::execute(AbstractEvolutionObject* object1)
{
	std::vector<double>* mutationStrength = object1->getMutationStrength();

	// Go through all mutationStrength values
	for (auto mutationStrengthValue = mutationStrength->begin(); mutationStrengthValue != mutationStrength->end(); mutationStrengthValue++)
	{
		// Shrink or grow the mutationStrength randomly: *= exp(changeSpeed * random);
		*mutationStrengthValue *= exp(mutationStrengthChangeSpeed * ((float)rand() / RAND_MAX * 2 - 1));
		// Make sure the values stays inside our boundaries
		*mutationStrengthValue = ( *mutationStrengthValue < 0 ? -1 : 1 ) * std::min(mutationStrengthMax, std::max(mutationStrengthMin, std::abs(*mutationStrengthValue)));
		// Change the mutation direction randomly (TODO: Make this variable)
		//if ((double)rand() / RAND_MAX > 0.5)
		//	*mutationStrengthValue *= -1;
	}

	auto weights = static_cast<FastLayeredNetwork*>(object1->getNeuralNetwork()->getNetworkTopology())->getWeights();
	int mutationStrengthIndex = 0;
	// Go through all edges
	for (auto neuron = weights->begin(); neuron != weights->end(); neuron++)
	{
		for (auto weight = neuron->begin(); weight != neuron->end(); weight++)
		{
			// Simply add the corresponding mutationStrength value to the weight (TODO: Maybe this step should be adjusted, because the original algorithm adds here an additional random factor)
			double weightAdd = (*mutationStrength)[mutationStrengthIndex] * ((float)rand() / RAND_MAX * 2 - 1);
			*weight += weightAdd;
			mutationStrengthIndex++;
		}
	}

}

void MutationAlgorithm::setMutationStrengthChangeSpeed(double mutationStrengthChangeSpeed_)
{
	mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
}

