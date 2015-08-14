// Includes
#include "NetworkTopology\LineStructure.hpp"
#include "NetworkTopology\SOMNetwork.hpp"

void LineStructure::initialize(SOMNetwork &somNetwork)
{
	double pos = 0;
	// Go through all neurons
	for (auto neuron = somNetwork.getNeurons()->front().begin(); neuron != somNetwork.getNeurons()->front().end(); neuron++)
	{
		neuronPositionsInStructure[*neuron].resize(1, pos);
		// Calculate the distance to all other neurons
		int d = 0;
		for (auto otherNeuron = neuron; otherNeuron != somNetwork.getNeurons()->front().end(); otherNeuron++)
		{
			// If the distance is 1, the two neurons are neighbors
			if (d == 1) 
			{
				neighborhoodNeurons[*neuron].push_back(*otherNeuron);
				neighborhoodNeurons[*otherNeuron].push_back(*neuron);
			}
			neighborhoodDistances[*neuron][*otherNeuron] = d;
			neighborhoodDistances[*otherNeuron][*neuron] = d;
			d++;
		}
		pos += 0.1;
	}
}
