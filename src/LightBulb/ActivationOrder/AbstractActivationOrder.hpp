#pragma once

#ifndef _ABSRACTACTIVATIONORDER_H_
#define _ABSTRACTACTIVATIONORDER_H_

// Includes
#include "Tools/AbstractCloneable.hpp"

// Library includes
#include <map>
#include <memory>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;
	class Edge;

	/**
	 * \brief Describes the order in which neurons should get activated
	 */
	class AbstractActivationOrder : public virtual AbstractCloneable
	{
	private:
	public:
		virtual ~AbstractActivationOrder() {}
		/**
		 * \brief Activates all Neurons in the given topology in a special order
		 * \param networkTopology The network to activate
		 */
		virtual void executeActivation(AbstractNetworkTopology &networkTopology) const = 0;
	};

}

#endif
