#pragma once

#ifndef _MOCKNETWORKTOPOLOGY_H_
#define _MOCKNETWORKTOPOLOGY_H_

#include "gmock/gmock.h"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

class MockNetworkTopology : public AbstractNetworkTopology
{
public:
	MOCK_METHOD0(getOutputActivationFunction, AbstractActivationFunction*());
	MOCK_METHOD1(getOutput, void(std::vector<std::pair<bool, double>>& outputVector));
	MOCK_METHOD1(setInput, void(std::vector<double>& inputVector));
	MOCK_METHOD1(getOutput, void(std::vector<double>& outputVector));
	MOCK_METHOD0(getNeurons, std::vector<std::vector<StandardNeuron*>>*());
	MOCK_METHOD2(randomizeWeights, void(double randStart, double randEnd));
	MOCK_METHOD0(getEdgeCount, int());
	MOCK_METHOD0(resetActivation, void());
	MOCK_METHOD1(getAllNeuronOutputs, void(std::map<AbstractNeuron*, double>& neuronOutputs));
	MOCK_METHOD1(getAllNeuronNetInputs, void(std::map<AbstractNeuron*, double>& neuronNetInputs));
	MOCK_METHOD0(getInputNeurons, std::vector<AbstractNeuron*>*());
	MOCK_METHOD0(getOutputNeurons, std::vector<StandardNeuron*>*());
	MOCK_METHOD0(getBiasNeuron, BiasNeuron*());
	MOCK_METHOD0(getOutputSize, int());
	MOCK_METHOD1(copyWeightsFrom, void(AbstractNetworkTopology& otherNetwork));
	MOCK_METHOD1(calculateEuclideanDistance, double(AbstractNetworkTopology& otherNetwork));
};

#endif
