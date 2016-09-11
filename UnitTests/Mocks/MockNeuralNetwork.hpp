#pragma once

#ifndef _MOCKNEURALNETWORK_H_
#define _MOCKNEURALNETWORK_H_

#include "gmock/gmock.h"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <ActivationOrder/AbstractActivationOrder.hpp>

class MockNeuralNetwork : public LightBulb::AbstractNeuralNetwork
{
public:
	MOCK_METHOD0(clone, AbstractNeuralNetwork* ());
	MOCK_METHOD8(calculate, void (std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, LightBulb::AbstractActivationOrder&, int, int, std::vector<std::map<LightBulb::AbstractNeuron*, double>>*, std::vector<std::map<LightBulb::AbstractNeuron*, double>>*, bool));
	MOCK_METHOD4(calculate, void (std::vector<double>&, std::vector<double>&, LightBulb::AbstractActivationOrder&, bool));
	MOCK_METHOD0(getNetworkTopology, LightBulb::AbstractNetworkTopology* ());
	MOCK_METHOD0(getName, std::string ());
	MOCK_METHOD1(setName, void (std::string));
	MOCK_METHOD0(getCreationDate, std::time_t ());
	MOCK_METHOD0(getState, LightBulb::NeuralNetworkState ());
	MOCK_METHOD1(setState, void (LightBulb::NeuralNetworkState));
	MOCK_METHOD0(getStateAsString, std::string ());
};

#endif
