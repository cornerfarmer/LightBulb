#pragma once

#ifndef _MOCKLAYEREDNETWORK_H_
#define _MOCKLAYEREDNETWORK_H_

#include "gmock/gmock.h"
#include "NetworkTopology/LayeredNetwork.hpp"

class MockLayeredNetwork : public LayeredNetwork
{
public:
	MOCK_METHOD1(refreshNetInputsForLayer, void(int layerNr));
	MOCK_METHOD1(refreshActivationsForLayer, void(int layerNr));
	MOCK_METHOD0(getLayerCount, int());
};

#endif
