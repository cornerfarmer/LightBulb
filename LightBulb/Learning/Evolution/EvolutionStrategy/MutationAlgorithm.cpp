// Includes
#include "Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
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
		*mutationStrengthValue *= exp(mutationStrengthChangeSpeed * distribution(generator));
		// Make sure the values stays inside our boundaries
		*mutationStrengthValue = ( *mutationStrengthValue < 0 ? -1 : 1 ) * std::min(mutationStrengthMax, std::max(mutationStrengthMin, std::abs(*mutationStrengthValue)));
		// Change the mutation direction randomly (TODO: Make this variable)
		//if ((double)rand() / RAND_MAX > 0.5)
		//	*mutationStrengthValue *= -1;
	}

	auto neurons = object1->getNeuralNetwork()->getNetworkTopology()->getNeurons();	
	int mutationStrengthIndex = 0;
	// Go through all edges
	for (auto layer = neurons->begin(); layer != neurons->end(); layer++)
	{		
		for (auto neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++)
			{
				// Simply add the corresponding mutationStrength value to the weight (TODO: Maybe this step should be adjusted, because the original algorithm adds here an additional random factor)
				double weightAdd = (*mutationStrength)[mutationStrengthIndex] * distribution(generator);
				(*edge)->setWeight((*edge)->getWeight() + weightAdd);
				mutationStrengthIndex++;
			}
		}
	}
}

void MutationAlgorithm::setMutationStrengthChangeSpeed(double mutationStrengthChangeSpeed_)
{
	mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
}

