#pragma once

#ifndef _ASYNCHRONOUSORDER_H_
#define _ASYNCHRONOUSORDER_H_

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"

// With this order, all neurons will get activated one after another
// This class is compatible with every sort of network
class AsynchronousOrder : public AbstractActivationOrder
{
private:
public:
	// Activates all neurons in the given topology one after another
	void executeActivation(AbstractNetworkTopology &networkTopology);
	// Inherited:
	AbstractActivationOrder* getCopy(); 
	std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(AbstractNetworkTopology &networkTopology);
};

#endif