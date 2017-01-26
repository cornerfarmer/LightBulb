#pragma once

#ifndef _ABSRACTACTIVATIONORDER_H_
#define _ABSTRACTACTIVATIONORDER_H_

// Includes
#include "LightBulb/Tools/AbstractCloneable.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

// Library includes
#include <map>
#include <memory>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

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
		virtual void executeActivation(AbstractNetworkTopology &networkTopology, const Vector<>* alternativeInput = nullptr) const = 0;
	};

}

#endif
