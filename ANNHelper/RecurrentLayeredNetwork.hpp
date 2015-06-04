#pragma once

#ifndef _RECURRENTLAYEREDNETWORK_H_
#define _RECURRENTLAYEREDNETWORK_H_

// Includes
#include "LayeredNetwork.hpp"
#include "RecurrentNetworkInterface.hpp"

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
class RecurrentLayeredNetwork : public LayeredNetwork, public RecurrentNetworkInterface
{
private:	
	// Build all recurrent connections
	void buildRecurrentConnections();
	// Returns our current options in form of a RecurrentLayeredNetworkOptions object
	RecurrentLayeredNetworkOptions* getOptions();
public:
	RecurrentLayeredNetwork(RecurrentLayeredNetworkOptions& options_);		
	// Inherited:
	std::unique_ptr<LayeredNetwork> unfold(int instanceCount);
	std::unique_ptr<std::map<Edge*, bool>> getNonRecurrentEdges();
};
#endif