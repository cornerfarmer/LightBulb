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
		/**
		 * \brief Returns a map which holds for every edge, if its two neurons are refreshed in the same timestep (In a feed forward with topological acitvation order for example are all edges in the same timestep) TODO: Refactor!
		 * \param networkTopology
		 * \return
		 */
		virtual std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(const AbstractNetworkTopology &networkTopology) const = 0;
	};

}

#endif
