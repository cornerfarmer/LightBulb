#pragma once

#ifndef _ASYNCHRONOUSORDER_H_
#define _ASYNCHRONOUSORDER_H_

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"

namespace LightBulb
{
	/**
	 * \brief Activates all neurons one after another. Compatible with every sort of network.
	 */
	class AsynchronousOrder : public AbstractActivationOrder
	{
	private:
	public:
		/**
		 * \brief Activates all neurons in the given topology one after another
		 * \param networkTopology The network to activate
		 */
		void executeActivation(AbstractNetworkTopology &networkTopology) const override;
		// Inherited:
		AbstractActivationOrder* getCopy() const override;
		std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(const AbstractNetworkTopology &networkTopology) const override;
	};
}

#endif