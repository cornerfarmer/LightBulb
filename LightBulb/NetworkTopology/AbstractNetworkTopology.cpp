#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"

void AbstractNetworkTopology::copyWeightsFrom(AbstractNetworkTopology& otherNetwork)
{
	// Go through all neuron groups of the deeper network
	int gOther = otherNetwork.getNeurons()->size() - 1;
	for (int g = getNeurons()->size() - 1; g >= 0 && gOther >= 0;)
	{
		// Extract the neurons in the current group of both networks
		std::vector<StandardNeuron*>& neuronsInGroup = (*getNeurons())[g];
		std::vector<StandardNeuron*>& neuronsInGroupOther = (*otherNetwork.getNeurons())[gOther];
		// Go through all neurons in the current network
		int neuronIndex = 0;
		std::vector<StandardNeuron*>::iterator neuronOther = neuronsInGroupOther.begin();
		for (std::vector<StandardNeuron*>::iterator neuron = neuronsInGroup.begin(); neuron != neuronsInGroup.end() && neuronOther != neuronsInGroupOther.end(); neuron++, neuronOther++, neuronIndex++)
		{
			// Extract all afferent edges of the current neurons
			std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
			std::list<Edge*>* afferentEdgesOther = (*neuronOther)->getAfferentEdges();
			// Go through all afferentEdges of the actual neurons
			std::list<Edge*>::iterator edgeOther = afferentEdgesOther->begin();
			for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end() && edgeOther != afferentEdgesOther->end(); edge++, edgeOther++)
			{	
				// Copy the weight from the edge from the other network into the edge of the own one
				(*edge)->setWeight((*edgeOther)->getWeight());
			}
		}

		// Go one group backwards in the other network
		gOther--;
		// If we reached the input layer and the otherNetwork is not as deep as the own one, then start from the last group in the other network again
		if (gOther == -1 && otherNetwork.getNeurons()->size() < getNeurons()->size())
			gOther = otherNetwork.getNeurons()->size() - 1;

		// Go one group backwards in the own network
		g--;
		// If we reached the input group and the own network is not as deep as the other one, then start from the last group in the own network again
		if (g == -1 && getNeurons()->size() - 1 < otherNetwork.getNeurons()->size())
			g = getNeurons()->size() - 1;
	}
}

