#pragma once

#ifndef _CASCADECORRELATIONNETWORK_H_
#define _CASCADECORRELATIONNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"

namespace LightBulb
{
	// Forward declarations


	// A CascadeCorrelationNetwork is layered network which has only one input and one output layer at the beginning. It grows while it learns.
	class CascadeCorrelationNetwork : public FeedForwardNetworkTopology
	{
	private:
	public:
		// Create a new CascadeCorrelationNetwork with the given input and output size
		CascadeCorrelationNetwork(unsigned int inputNeuronCount, unsigned int outputNeuronCount);
	};
}

#endif