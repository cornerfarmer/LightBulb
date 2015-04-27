#pragma once

#ifndef _ABSRACTACTIVATIONORDER_H_
#define _ABSTRACTACTIVATIONORDER_H_

// Forward declarations
class AbstractNetworkTopology;

// This class describes the order, how neurons should get activated
class AbstractActivationOrder
{
private:
public:
	virtual ~AbstractActivationOrder() {}
	// Activates all Neurons in the given topology in a special order
	virtual void executeActivation(AbstractNetworkTopology &networkTopology) = 0;
	virtual AbstractActivationOrder* getCopy() = 0; 
};

#endif