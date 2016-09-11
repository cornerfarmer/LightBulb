#pragma once

#ifndef _MOCKACTIVATIONORDER_H_
#define _MOCKACTIVATIONORDER_H_

#include "gmock/gmock.h"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

class MockActivationOrder : public LightBulb::AbstractActivationOrder
{
public:
	MOCK_METHOD1(executeActivation, void(LightBulb::AbstractNetworkTopology& networkTopology));
	MOCK_METHOD0(getCopy, AbstractActivationOrder*());
	
	std::unique_ptr<std::map<LightBulb::Edge*, bool>> getSameTimestepEdges(LightBulb::AbstractNetworkTopology& networkTopology)
	{
		return std::unique_ptr<std::map<LightBulb::Edge*, bool>>(getSameTimestepEdgesProxy(networkTopology));
	}
	MOCK_METHOD1(getSameTimestepEdgesProxy, std::map<LightBulb::Edge*, bool>*(LightBulb::AbstractNetworkTopology& networkTopology));
};

#endif
