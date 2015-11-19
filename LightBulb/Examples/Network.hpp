#pragma once

#ifndef _NETWORK_H_
#define _NETWORK_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"

// Forward declarations
class EvolutionLearningRule;
class NetworkSimulator;

class Network : public AbstractSimpleEvolutionObject
{
protected:
	NetworkSimulator* networkSimulator;
	std::vector<std::vector<float>> positions;
	NeuralNetworkIO<double> getNNInput();
	void interpretNNOutput(NeuralNetworkIO<double>* output);
public:	
	Network(NetworkSimulator* networkSimulator_);
	~Network();
	std::vector<std::vector<float>>* getPositions();
};
#endif
