#pragma once

#ifndef _MOCKFeedForwardNetworkTopology_H_
#define _MOCKFeedForwardNetworkTopology_H_

#include "gmock/gmock.h"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

class MockFeedForwardNetworkTopology : public LightBulb::FeedForwardNetworkTopology
{
public:
	MOCK_METHOD2(refreshNetInputsForLayer, void (int, const LightBulb::Vector<>*));
	MOCK_METHOD1(refreshActivationsForLayer, void (int));
	MOCK_CONST_METHOD0(getLayerCount, int());
};

#endif
