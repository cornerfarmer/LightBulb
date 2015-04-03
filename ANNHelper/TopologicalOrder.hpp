#pragma once

#ifndef _TOPOLOGICALORDER_H_
#define _TOPOLOGICALORDER_H_

#include "ActivationOrder.hpp"

class TopologicalOrder : ActivationOrder
{
private:
public:
	TopologicalOrder();
	void executeActivation(NetworkTopology &networkTopology);
};

#endif