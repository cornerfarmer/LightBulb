#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "LayeredNetwork.hpp"

void AbstractNetworkTopology::copyWeightsFrom(AbstractNetworkTopology& otherNetwork)
{
	int firstLayer = (dynamic_cast<LayeredNetwork*>(this) ? 1 : 0);
	int firstLayerOther = (dynamic_cast<LayeredNetwork*>(&otherNetwork) ? 1 : 0);
	// Go through all neuron groups of the deeper network
	int gOther = otherNetwork.getNeurons()->size() - 1;
	for (int g = getNeurons()->size() - 1; g >= firstLayer && gOther >= firstLayerOther;)
	{
		// Extract the neurons in the current group of both networks
		std::vector<AbstractNeuron*>& neuronsInGroup = (*getNeurons())[g];
		std::vector<AbstractNeuron*>& neuronsInGroupOther = (*otherNetwork.getNeurons())[gOther];
		// Go through all neurons in the current network
		int neuronIndex = 0;
		std::vector<AbstractNeuron*>::iterator neuronOther = neuronsInGroupOther.begin();
		for (std::vector<AbstractNeuron*>::iterator neuron = neuronsInGroup.begin(); neuron != neuronsInGroup.end() && neuronOther != neuronsInGroupOther.end(); neuron++, neuronOther++, neuronIndex++)
		{
			// Extract all afferent edges of the current neurons
			std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
			std::list<Edge*>* afferentEdgesOther = (dynamic_cast<StandardNeuron*>(*neuronOther))->getAfferentEdges();
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
		if (gOther == firstLayerOther - 1 && otherNetwork.getNeurons()->size() < getNeurons()->size())
			gOther = otherNetwork.getNeurons()->size() - 1;

		// Go one group backwards in the own network
		g--;
		// If we reached the input group and the own network is not as deep as the other one, then start from the last group in the own network again
		if (g == firstLayer && getNeurons()->size() - 1 < otherNetwork.getNeurons()->size())
			g = getNeurons()->size() - 1;
	}
}