#pragma once

#ifndef _MOCKACTIVATIONORDER_H_
#define _MOCKACTIVATIONORDER_H_

#include "gmock/gmock.h"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

class MockActivationOrder : public AbstractActivationOrder
{
public:
	MOCK_METHOD1(executeActivation, void(AbstractNetworkTopology& networkTopology));
	MOCK_METHOD0(getCopy, AbstractActivationOrder*());
	
	std::unique_ptr<std::map<Edge*, bool>> getSameTimestepEdges(AbstractNetworkTopology& networkTopology)
	{
		return std::unique_ptr<std::map<Edge*, bool>>(getSameTimestepEdgesProxy(networkTopology));
	}
	MOCK_METHOD1(getSameTimestepEdgesProxy, std::map<Edge*, bool>*(AbstractNetworkTopology& networkTopology));
};

#endif
