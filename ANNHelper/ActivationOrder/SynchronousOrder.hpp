#pragma once

#ifndef _SYNCHRONOUSORDER_H_
#define _SYNCHRONOUSORDER_H_

// Includes
#include "AbstractActivationOrder.hpp"

// With this order, all neurons will get activated at the same timestep
// This class is only compatible with every sort of network
class SynchronousOrder : public AbstractActivationOrder
{
private:
public:
	// Activates all neurons in the given layered(!) topology in a topological order
	void executeActivation(AbstractNetworkTopology &networkTopology);
	// Inherited:
	AbstractActivationOrder* getCopy(); 
	std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(AbstractNetworkTopology &networkTopology);
};

#endif