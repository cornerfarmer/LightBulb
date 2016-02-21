#pragma once

#ifndef _NEURONCOMPARETHRESHOLD_H_
#define _NEURONCOMPARETHRESHOLD_H_

// Includes

// Library Includes
#include <vector>

//Forward declarations
class StandardNeuron;

// A NeuronCompareThreshold holds a vector of neurons which will be compared
class NeuronCompareThreshold : public AbstractThreshold
{
private:
	std::vector<StandardNeuron*>* neurons;
public:
	NeuronCompareThreshold(std::vector<StandardNeuron*>* neurons_);
	std::vector<StandardNeuron*>* getNeurons();
	void setNeurons(std::vector<StandardNeuron*>* neurons_);
	AbstractThreshold* getCopy();
};

#endif