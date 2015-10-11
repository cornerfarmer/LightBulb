// Includes
#include "Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"

void RecombinationAlgorithm::execute(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2)
{
	auto neurons1 = object1->getNeuralNetwork()->getNetworkTopology()->getNeurons();
	auto neurons2 = object1->getNeuralNetwork()->getNetworkTopology()->getNeurons();
	auto layer1 = neurons1->begin();
	for (auto layer2 = neurons2->begin(); layer1 != neurons1->end() && layer2 != neurons2->end(); layer1++, layer2++)
	{
		auto neuron1 = layer1->begin();
		for (auto neuron2 = layer2->begin(); neuron1 != layer1->end() && neuron2 != layer2->end(); neuron1++, neuron2++)
		{
			auto edge1 = (*neuron1)->getAfferentEdges()->begin();
			for (auto edge2 = (*neuron2)->getAfferentEdges()->begin(); edge1 != (*neuron1)->getAfferentEdges()->end() && edge2 != (*neuron2)->getAfferentEdges()->begin(); edge1++, edge2++)
			{
				(*edge1)->setWeight(((*edge1)->getWeight() + (*edge2)->getWeight()) / 2);
			}
		}
	}
}