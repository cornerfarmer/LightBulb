#pragma once

#ifndef _MOCKFeedForwardNetworkTopology_H_
#define _MOCKFeedForwardNetworkTopology_H_

#include "gmock/gmock.h"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

class MockFeedForwardNetworkTopology : public LightBulb::FeedForwardNetworkTopology
{
public:
	MOCK_METHOD1(refreshNetInputsForLayer, void(int layerNr));
	MOCK_METHOD1(refreshActivationsForLayer, void(int layerNr));
	MOCK_CONST_METHOD0(getLayerCount, int());
};

#endif
