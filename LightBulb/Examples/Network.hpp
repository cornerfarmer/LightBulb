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
	void getNNInput(std::vector<double>& input);
	void interpretNNOutput(std::vector<double>& output);
public:	
	Network(NetworkSimulator* networkSimulator_);
	~Network();
	std::vector<std::vector<float>>* getPositions();
};
#endif
