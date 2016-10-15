#pragma once

#ifndef _SYNCHRONOUSORDER_H_
#define _SYNCHRONOUSORDER_H_

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"

namespace LightBulb
{
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
		void executeActivation(AbstractNetworkTopology &networkTopology) const override;
		// Inherited:
		AbstractActivationOrder* getCopy() const override;
		std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(const AbstractNetworkTopology &networkTopology) const override;
	};
}

#endif