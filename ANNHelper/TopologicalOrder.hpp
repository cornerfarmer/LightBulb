#pragma once

#ifndef _TOPOLOGICALORDER_H_
#define _TOPOLOGICALORDER_H_

// Includes
#include "ActivationOrder.hpp"

// With this order, neurons will get activated layer by layer
// This class is only compatible with a LayeredNetwork!
class TopologicalOrder : public ActivationOrder
{
private:
public:
	// Activates all neurons in the given layered(!) topology in a topological order
	void executeActivation(NetworkTopology &networkTopology);
};

#endif