#pragma once

#ifndef _ABSRACTACTIVATIONORDER_H_
#define _ABSTRACTACTIVATIONORDER_H_

// Library includes
#include <map>
#include <memory>

// Forward declarations
class AbstractNetworkTopology;
class Edge;

// This class describes the order, how neurons should get activated
class AbstractActivationOrder
{
private:
public:
	virtual ~AbstractActivationOrder() {}
	// Activates all Neurons in the given topology in a special order
	virtual void executeActivation(AbstractNetworkTopology &networkTopology) = 0;
	// Retruns a copy of this activation order
	virtual AbstractActivationOrder* getCopy() = 0; 
	// Returns a map which holds for every edge, if its two neurons are refreshed in the same timestep (In a feed forward with topological acitvation order for example are all edges in the same timestep)
	virtual std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(AbstractNetworkTopology &networkTopology) = 0;
};

#endif
