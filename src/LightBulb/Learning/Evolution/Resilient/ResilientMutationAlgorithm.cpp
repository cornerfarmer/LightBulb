// Includes
#include "Learning/Evolution/Resilient/ResilientMutationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"
#include <math.h>


ResilientMutationAlgorithm::ResilientMutationAlgorithm()
{
	focusedEdgeIndex = 0;
}

void ResilientMutationAlgorithm::execute(AbstractEvolutionObject* object1)
{
	std::vector<double>* mutationStrength = object1->getMutationStrength();

	auto neurons = object1->getNeuralNetwork()->getNetworkTopology()->getNeurons();	
	int edgeIndex = 0;
	// Go through all edges
	for (auto layer = neurons->begin(); layer != neurons->end(); layer++)
	{		
		for (auto neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++)
			{
				if (edgeIndex == focusedEdgeIndex) {
					// Simply add the corresponding mutationStrength value to the weight (TODO: Maybe this step should be adjusted, because the original algorithm adds here an additional random factor)
					double weightAdd = (*mutationStrength)[edgeIndex] * direction;
					(*edge)->setWeight((*edge)->getWeight() + weightAdd);
					return;
				}
				edgeIndex++;
			}
		}
	}
}

void ResilientMutationAlgorithm::setFocusedEdgeIndex(int newFocusedEdgeIndex)
{
	focusedEdgeIndex = newFocusedEdgeIndex;
}



void ResilientMutationAlgorithm::setDirection(int newDirection)
{
	direction = newDirection;
}
