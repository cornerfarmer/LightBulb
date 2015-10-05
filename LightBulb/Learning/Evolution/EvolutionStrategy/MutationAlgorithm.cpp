// Includes
#include "Learning\Evolution\EvolutionStrategy\MutationAlgorithm.hpp"
#include "Learning\Evolution\AbstractEvolutionObject.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include <math.h>
#include <random>

void MutationAlgorithm::execute(AbstractEvolutionObject* object1)
{
	std::vector<double>* mutationStrength = object1->getMutationStrength();
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 1.0);

	for (auto mutationStrengthValue = mutationStrength->begin(); mutationStrengthValue != mutationStrength->end(); mutationStrengthValue++)
	{
		*mutationStrengthValue *= exp(0.1 * distribution(generator));
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

