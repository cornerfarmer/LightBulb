#pragma once

#ifndef _ACTIVATIONORDER_H_
#define _ACTIVATIONORDER_H_

// Forward declarations
class NetworkTopology;

// This class describes the order, how neurons should get activated
class ActivationOrder
{
private:
public:
	virtual ~ActivationOrder() {}
	// Activates all Neurons in the given topology in a special order
	virtual void executeActivation(NetworkTopology &networkTopology) = 0;
};

#endif