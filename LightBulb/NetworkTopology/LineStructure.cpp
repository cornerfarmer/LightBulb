// Includes
#include "NetworkTopology\LineStructure.hpp"
#include "NetworkTopology\SOMNetwork.hpp"

void LineStructure::initialize(SOMNetwork &somNetwork)
{
	double pos = 0;
	for (auto neuron = somNetwork.getNeurons()->front().begin(); neuron != somNetwork.getNeurons()->front().end(); neuron++)
	{
		neuronPositionsInStructure[*neuron].resize(1, pos);
		int d = 0;
		for (auto otherNeuron = neuron; otherNeuron != somNetwork.getNeurons()->front().end(); otherNeuron++)
		{
			neighborhoodDistances[*neuron][*otherNeuron] = d;
			neighborhoodDistances[*otherNeuron][*neuron] = d;
			d++;
		}
		pos += 0.1;
	}

}
