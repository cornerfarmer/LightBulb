#pragma once

#ifndef _TOPOLOGICALORDER_H_
#define _TOPOLOGICALORDER_H_

// Includes
#include "ActivationOrder.hpp"

// With this order, neurons will get activated layer by layer
// This class is only compatible with a LayeredNetwork!
class TopologicalOrder : ActivationOrder
{
private:
public:
	TopologicalOrder();
	void executeActivation(NetworkTopology &networkTopology);
};

#endif