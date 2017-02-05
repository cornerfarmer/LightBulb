#pragma once

#ifndef _NETWORK_H_
#define _NETWORK_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractDefaultIndividual.hpp"

// Forward declarations
class NetworkSimulator;

class Network : public LightBulb::AbstractDefaultIndividual
{
	template <class Archive>
	friend void save(Archive& archive, Network const& individual);
	template <class Archive>
	friend void load(Archive& archive, Network& individual);
protected:
	LightBulb::Vector<> positions;
	bool inputIsSet;
	void getNNInput(LightBulb::Vector<>& input) override;
	void interpretNNOutput(const LightBulb::Vector<>& output) override;
public:	
	Network(NetworkSimulator& networkSimulator_);
	Network() = default;
	~Network();
	const LightBulb::Vector<>& getPositions() const;
};

#include "IO/NetworkIO.hpp"

#endif
