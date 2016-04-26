#pragma once

#ifndef _NETWORK_H_
#define _NETWORK_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class EvolutionLearningRule;
class NetworkSimulator;

class Network : public AbstractSimpleEvolutionObject
{
	template <class Archive>
	friend void save(Archive& archive, Network const& object);
	template <class Archive>
	friend void load(Archive& archive, Network& object);
protected:
	std::vector<std::vector<float>> positions;
	void getNNInput(std::vector<double>& input);
	void interpretNNOutput(std::vector<double>& output);
public:	
	Network(NetworkSimulator* networkSimulator_);
	Network() = default;
	~Network();
	std::vector<std::vector<float>>* getPositions();
};

#include "IO/NetworkIO.hpp"

#endif
