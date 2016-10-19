#pragma once

#ifndef _MOCKNEURALNETWORK_H_
#define _MOCKNEURALNETWORK_H_

#include "gmock/gmock.h"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <ActivationOrder/AbstractActivationOrder.hpp>

class MockNeuralNetwork : public LightBulb::AbstractNeuralNetwork
{
public:
	MOCK_CONST_METHOD0(clone, AbstractNeuralNetwork* ());
	MOCK_METHOD8(calculate, void (const std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, const LightBulb::AbstractActivationOrder&, int, int, std::vector<std::map<LightBulb::AbstractNeuron*, double>>*, std::vector<std::map<LightBulb::AbstractNeuron*, double>>*, bool));
	MOCK_METHOD4(calculate, void (const std::vector<double>&, std::vector<double>&, const LightBulb::AbstractActivationOrder&, bool));
	MOCK_CONST_METHOD0(getNetworkTopology, LightBulb::AbstractNetworkTopology* ());
	MOCK_CONST_METHOD0(getName, const std::string& ());
	MOCK_METHOD1(setName, void (const std::string&));
	MOCK_CONST_METHOD0(getCreationDate, const std::time_t& ());
	MOCK_CONST_METHOD0(getState, const LightBulb::NeuralNetworkState& ());
	MOCK_METHOD1(setState, void (LightBulb::NeuralNetworkState));
	MOCK_CONST_METHOD0(getStateAsString, const std::string ());
};

#endif
