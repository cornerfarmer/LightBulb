#pragma once

#ifndef _MOCKNEURALNETWORK_H_
#define _MOCKNEURALNETWORK_H_

#include "gmock/gmock.h"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <ActivationOrder/AbstractActivationOrder.hpp>

class MockNeuralNetwork : public AbstractNeuralNetwork
{
public:
	MOCK_METHOD0(getNetworkTopology, AbstractNetworkTopology* ());
	MOCK_METHOD8(calculate, void (std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, AbstractActivationOrder&, int, int, std::vector<std::map<AbstractNeuron*, double>>*, std::vector<std::map<AbstractNeuron*, double>>*, bool));
	MOCK_METHOD4(calculate, void (std::vector<double>&, std::vector<double>&, AbstractActivationOrder&, bool));
	MOCK_METHOD0(getName, std::string ());
	MOCK_METHOD0(getCreationDate, std::time_t ());
	MOCK_METHOD0(getState, NeuralNetworkState ());
	MOCK_METHOD1(setState, void (NeuralNetworkState));
	MOCK_METHOD0(getStateAsString, std::string ());
	MOCK_METHOD0(clone, AbstractNeuralNetwork* ());
	MOCK_METHOD1(setName, void (std::string));
};

#endif
