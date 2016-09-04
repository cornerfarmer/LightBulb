#pragma once

#ifndef _RECURRENTFeedForwardNetworkTopology_H_
#define _RECURRENTFeedForwardNetworkTopology_H_

// Includes
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/RecurrentNetworkInterface.hpp"

// This struct contains all options needed to build a RecurrentFeedForwardNetworkTopology
struct RecurrentFeedForwardNetworkTopologyOptions : public FeedForwardNetworkTopologyOptions
{	
	// Enables edges from the output neurons to the first hidden layer neurons 
	bool connectOutputWithInnerNeurons;
	// Enables edges between all neurons inside a hidden layer
	bool selfConnectHiddenLayers;
	// Enables edges between all neurons inside the output layer
	bool selfConnectOutputLayers;
	RecurrentFeedForwardNetworkTopologyOptions()
	{
		connectOutputWithInnerNeurons = false;
		selfConnectHiddenLayers = false;
		selfConnectOutputLayers = false;
	}
};

// A RecurrentFeedForwardNetworkTopology describes a FeedForwardNetworkTopology with recurrent connections
class RecurrentFeedForwardNetworkTopology : public FeedForwardNetworkTopology, public RecurrentNetworkInterface
{
private:	
	// Build all recurrent connections
	void buildRecurrentConnections();
	// Returns our current options in form of a RecurrentFeedForwardNetworkTopologyOptions object
	RecurrentFeedForwardNetworkTopologyOptions* getOptions();
public:
	RecurrentFeedForwardNetworkTopology(RecurrentFeedForwardNetworkTopologyOptions& options_);		
	// Inherited:
	std::unique_ptr<FeedForwardNetworkTopology> unfold(int instanceCount) override;
	std::unique_ptr<std::map<Edge*, bool>> getNonRecurrentEdges();
	void horizontalMergeWith(RecurrentFeedForwardNetworkTopology& otherNetwork);
};
#endif