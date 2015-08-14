#pragma once

#ifndef _ABSTRACTSOMSTRUCTURE_H_
#define _ABSTRACTSOMSTRUCTURE_H_

// Libary includes
#include <map>
#include <vector>
#include <list>

// Includes

// Forward declarations
class StandardNeuron;
class SOMNetwork;

// Describes the internal structure of a neuron
class AbstractSOMStructure
{
protected:	
	// Holds the neighborhood neurons of all neurons
	std::map<StandardNeuron*, std::list<StandardNeuron*>> neighborhoodNeurons;
	// Holds the distance between all neurons
	std::map<StandardNeuron*, std::map<StandardNeuron*, double>> neighborhoodDistances;
	// Holds the coordinates of every neuron inside the structure (Only used by graphical classes)
	std::map<StandardNeuron*, std::vector<float>> neuronPositionsInStructure;
public:
	virtual void initialize(SOMNetwork &somNetwork) = 0;
	std::map<StandardNeuron*, std::map<StandardNeuron*, double>>* getNeighborhoodDistances();
	std::map<StandardNeuron*, std::vector<float>>* getNeuronPositionsInStructure();
	std::map<StandardNeuron*, std::list<StandardNeuron*>>* getNeighborhoodNeurons();

};

#endif