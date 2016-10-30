#pragma once

#ifndef _MOCKACTIVATIONORDER_H_
#define _MOCKACTIVATIONORDER_H_

#include "gmock/gmock.h"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

class MockActivationOrder : public LightBulb::AbstractActivationOrder
{
public:
	MOCK_CONST_METHOD1(executeActivation, void (LightBulb::AbstractNetworkTopology&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());

	std::unique_ptr<std::map<LightBulb::Edge*, bool>> getSameTimestepEdges(const LightBulb::AbstractNetworkTopology& networkTopology) const
	{
		return std::unique_ptr<std::map<LightBulb::Edge*, bool>>(getSameTimestepEdgesProxy(networkTopology));
	}
	MOCK_CONST_METHOD1(getSameTimestepEdgesProxy, std::map<LightBulb::Edge*, bool>*(const LightBulb::AbstractNetworkTopology& networkTopology));

};

#endif
