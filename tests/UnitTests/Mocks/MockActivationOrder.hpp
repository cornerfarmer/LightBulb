#pragma once

#ifndef _MOCKACTIVATIONORDER_H_
#define _MOCKACTIVATIONORDER_H_

#include "gmock/gmock.h"
#include "LightBulb/ActivationOrder/AbstractActivationOrder.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"

class MockActivationOrder : public LightBulb::AbstractActivationOrder
{
public:
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
	MOCK_CONST_METHOD2(executeActivation, void (LightBulb::AbstractNetworkTopology&, const LightBulb::Vector*));
};

#endif
