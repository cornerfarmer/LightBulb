// Includes
#include "NetworkTopology/AbstractSOMStructure.hpp"

std::map<StandardNeuron*, std::map<StandardNeuron*, double>>* AbstractSOMStructure::getNeighborhoodDistances()
{
	return &neighborhoodDistances;
}

std::map<StandardNeuron*, std::vector<float>>* AbstractSOMStructure::getNeuronPositionsInStructure()
{
	return &neuronPositionsInStructure;
}

std::map<StandardNeuron*, std::list<StandardNeuron*>>*  AbstractSOMStructure::getNeighborhoodNeurons()
{
	return &neighborhoodNeurons;
}

