#pragma once

#ifndef _SYNCHRONOUSORDER_H_
#define _SYNCHRONOUSORDER_H_

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"

// With this order, all neurons will get activated at the same timestep
// This class is only compatible with every sort of network
class SynchronousOrder : public AbstractActivationOrder
{
private:
public:
	// Activates all neurons in the given topology 
	void executeActivation(AbstractNetworkTopology &networkTopology) override;
	// Inherited:
	AbstractActivationOrder* getCopy() override; 
	std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(AbstractNetworkTopology &networkTopology) override;
};

#endif