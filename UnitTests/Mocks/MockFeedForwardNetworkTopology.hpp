#pragma once

#ifndef _MOCKFeedForwardNetworkTopology_H_
#define _MOCKFeedForwardNetworkTopology_H_

#include "gmock/gmock.h"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"

class MockFeedForwardNetworkTopology : public FeedForwardNetworkTopology
{
public:
	MOCK_METHOD1(refreshNetInputsForLayer, void(int layerNr));
	MOCK_METHOD1(refreshActivationsForLayer, void(int layerNr));
	MOCK_METHOD0(getLayerCount, int());
};

#endif
