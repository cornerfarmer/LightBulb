#pragma once

#ifndef _ABSTRACTFEEDFORWARDNETWORKTOPOLOGY_H_
#define _ABSTRACTFEEDFORWARDNETWORKTOPOLOGY_H_

// Libary includes

// Includes
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	// Forward declarations

	/**
	 * \brief A feed forward network describes a network which has only forward connections.
	 * \details It has one input layer, multiple "hidden" layers and one output layer.
	 * The activation is forward propagated, so the network has no internal state.
	 */
	class AbstractFeedForwardNetworkTopology : public AbstractNetworkTopology
	{
	protected:
	public:
	};
}

#endif
