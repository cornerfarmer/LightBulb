#pragma once

#ifndef _MOCKNEURALNETWORK_H_
#define _MOCKNEURALNETWORK_H_

#include "gmock/gmock.h"
#include <LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <LightBulb/ActivationOrder/AbstractActivationOrder.hpp>

class MockNeuralNetwork : public LightBulb::AbstractNeuralNetwork
{
public:
	MOCK_CONST_METHOD0(clone, AbstractNeuralNetwork* ());
	MOCK_METHOD4(calculate, void (const std::vector<double>&, std::vector<double>&, const LightBulb::AbstractActivationOrder&, bool));
	MOCK_CONST_METHOD0(getNetworkTopology, LightBulb::AbstractNetworkTopology& ());
	MOCK_CONST_METHOD0(getName, const std::string& ());
	MOCK_METHOD1(setName, void (const std::string&));
	MOCK_CONST_METHOD0(getCreationDate, const std::time_t& ());
	MOCK_CONST_METHOD0(getState, const LightBulb::NeuralNetworkState& ());
	MOCK_METHOD1(setState, void (LightBulb::NeuralNetworkState));
	MOCK_CONST_METHOD0(getStateAsString, std::string ());
	MOCK_METHOD3(calculate, std::vector<double> (const std::vector<double>&, const LightBulb::AbstractActivationOrder&, bool));
	MOCK_METHOD3(calculate, void (const std::vector<double>&, std::vector<double>&, bool));
	MOCK_METHOD2(calculate, std::vector<double> (const std::vector<double>&, bool));
	MOCK_METHOD3(calculateWithoutOutputCopy, const LightBulb::Vector<>& (const LightBulb::Vector<>&, const LightBulb::AbstractActivationOrder&, bool));
};

#endif
