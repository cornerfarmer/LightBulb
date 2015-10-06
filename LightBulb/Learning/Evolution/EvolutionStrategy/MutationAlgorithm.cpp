// Includes
#include "Learning\Evolution\EvolutionStrategy\MutationAlgorithm.hpp"
#include "Learning\Evolution\AbstractEvolutionObject.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include <math.h>


MutationAlgorithm::MutationAlgorithm()
{
	distribution = std::normal_distribution<double>(0, 1);
}

void MutationAlgorithm::execute(AbstractEvolutionObject* object1)
{
	std::vector<double>* mutationStrength = object1->getMutationStrength();

	for (auto mutationStrengthValue = mutationStrength->begin(); mutationStrengthValue != mutationStrength->end(); mutationStrengthValue++)
	{
		*mutationStrengthValue *= exp(0.4 * distribution(generator));
		if ((double)rand() / RAND_MAX > 0.9)
			*mutationStrengthValue *= -1;
	}

	auto neurons = object1->getNeuralNetwork()->getNetworkTopology()->getNeurons();	
	int mutationStrengthIndex = 0;
	for (auto layer = neurons->begin(); layer != neurons->end(); layer++)
	{		
		for (auto neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++)
			{
				(*edge)->setWeight((*edge)->getWeight() + (*mutationStrength)[mutationStrengthIndex]);
				mutationStrengthIndex++;
			}
		}
	}
}

