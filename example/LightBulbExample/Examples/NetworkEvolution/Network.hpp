#pragma once

#ifndef _NETWORK_H_
#define _NETWORK_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractDefaultIndividual.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class NetworkSimulator;

class Network : public LightBulb::AbstractDefaultIndividual
{
	template <class Archive>
	friend void save(Archive& archive, Network const& individual);
	template <class Archive>
	friend void load(Archive& archive, Network& individual);
protected:
	std::vector<std::vector<float>> positions;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:	
	Network(NetworkSimulator& networkSimulator_);
	Network() = default;
	~Network();
	const std::vector<std::vector<float>>& getPositions() const;
};

#include "IO/NetworkIO.hpp"

#endif
