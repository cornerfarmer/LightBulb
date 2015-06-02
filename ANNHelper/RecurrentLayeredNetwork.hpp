#pragma once

#ifndef _RECURRENTNETWORK_H_
#define _RECURRENTNETWORK_H_

// Includes
#include "LayeredNetwork.hpp"

// This struct contains all options needed to build a RecurrentLayeredNetwork
struct RecurrentLayeredNetworkOptions : public LayeredNetworkOptions
{	
	bool connectOutputWithInnerNeurons;
	bool selfConnectHiddenLayers;
	bool selfConnectOutputLayers;
	RecurrentLayeredNetworkOptions()
	{
		connectOutputWithInnerNeurons = false;
		selfConnectHiddenLayers = false;
		selfConnectOutputLayers = false;
	}
};

// A RecurrentLayeredNetwork describes a LayeredNetwork with recurrent connections
class RecurrentLayeredNetwork : public LayeredNetwork
{
private:	
	// Build all recurrent connections
	void buildRecurrentConnections();
	// Returns our current options in form of a RecurrentLayeredNetworkOptions object
	RecurrentLayeredNetworkOptions* getOptions();
public:
	RecurrentLayeredNetwork(RecurrentLayeredNetworkOptions& options_);		
	std::unique_ptr<LayeredNetwork> RecurrentLayeredNetwork::unfold(int instanceCount);
	std::unique_ptr<std::map<Edge*, bool>> getNonRecurrentEdges();
};
#endif