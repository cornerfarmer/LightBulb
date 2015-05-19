#pragma once

#ifndef _RECURRENTNETWORK_H_
#define _RECURRENTNETWORK_H_

// Includes
#include "LayeredNetwork.hpp"

// This struct contains all options needed to build a RecurrentNetwork
struct RecurrentNetworkOptions : public LayeredNetworkOptions
{	
	bool connectOutputWithInnerNeurons;
	RecurrentNetworkOptions()
	{
		connectOutputWithInnerNeurons = false;
	}
};

// A RecurrentNetwork describes a LayeredNetwork with recurrent connections
class RecurrentNetwork : public LayeredNetwork
{
private:	
	// Build all recurrent connections
	void buildRecurrentConnections();
	// Returns our current options in form of a RecurrentNetworkOptions object
	RecurrentNetworkOptions* getOptions();
public:
	RecurrentNetwork(RecurrentNetworkOptions& options_);		
	std::unique_ptr<LayeredNetwork> RecurrentNetwork::unfold(int instanceCount);
};

#endif