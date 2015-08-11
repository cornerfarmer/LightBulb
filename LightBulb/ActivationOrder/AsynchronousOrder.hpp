#pragma once

#ifndef _ASYNCHRONOUSORDER_H_
#define _ASYNCHRONOUSORDER_H_

// Includes
#include "ActivationOrder\AbstractActivationOrder.hpp"

// With this order, all neurons will get activated one after another
// This class is only compatible with every sort of network
class AsynchronousOrder : public AbstractActivationOrder
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