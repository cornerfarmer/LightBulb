#pragma once

#ifndef _TOPOLOGICALORDER_H_
#define _TOPOLOGICALORDER_H_

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"

// With this order, neurons will get activated layer by layer
// This class is only compatible with a LayeredNetwork!
class TopologicalOrder : public AbstractActivationOrder
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