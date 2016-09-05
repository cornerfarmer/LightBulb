#pragma once

#ifndef _SYNCHRONOUSORDER_H_
#define _SYNCHRONOUSORDER_H_

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"

/**
 * \brief With this order, all neurons will get activated at the same timestep. Compatible with every sort of network.
 */
class SynchronousOrder : public AbstractActivationOrder
{
private:
public:
	/**
	 * \brief Activates all neurons in the given topology
	 * \param networkTopology The network to activate
	 */
	void executeActivation(AbstractNetworkTopology &networkTopology) override;
	// Inherited:
	AbstractActivationOrder* getCopy() override; 
	std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(AbstractNetworkTopology &networkTopology) override;
};

#endif