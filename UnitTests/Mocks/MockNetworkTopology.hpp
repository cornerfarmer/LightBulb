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

	MOCK_METHOD0(getInnerActivationFunction, AbstractActivationFunction* ());
	MOCK_METHOD1(getNeuronCountInLayer, int (int));
	MOCK_METHOD0(getLayerCount, int ());
	MOCK_METHOD2(getAfferentEdgeCount, int (int, int));
	MOCK_METHOD3(getPrevNeuronActivation, double (int, int, int));
	MOCK_METHOD3(getWeight, double (int, int, int));
	MOCK_METHOD4(setWeight, void (int, int, int, double));
	MOCK_METHOD2(getNetInput, double (int, int));
	MOCK_METHOD1(getNetInputVector, Eigen::VectorXd (int));
	MOCK_METHOD2(getEfferentWeightVector, Eigen::VectorXd (int, int));
	MOCK_METHOD1(getActivationVector, Eigen::VectorXd (int));
	MOCK_METHOD1(getAfferentWeightsPerLayer, Eigen::MatrixXd (int));
	MOCK_METHOD1(getEfferentWeightsPerLayer, Eigen::MatrixXd (int));
	MOCK_METHOD2(setAfferentWeightsPerLayer, void (int, Eigen::MatrixXd&));
	MOCK_METHOD0(getWeights, std::vector<Eigen::MatrixXd>* ());
	MOCK_METHOD0(getNeuronCountsPerLayer, std::vector<unsigned> ());
	MOCK_METHOD2(removeNeuron, void (int, int));
	MOCK_METHOD1(addNeuron, void (int));
	MOCK_METHOD0(usesBiasNeuron, bool ());
	MOCK_METHOD3(removeAfferentWeight, void (int, int, int));
	MOCK_METHOD3(existsAfferentWeight, bool (int, int, int));
	MOCK_METHOD0(getNeuronCount, int ());
	MOCK_METHOD0(clone, AbstractNetworkTopology* ());
	MOCK_METHOD0(getActivationsCopy, std::vector<Eigen::VectorXd> ());
	MOCK_METHOD0(getNetInputs, std::vector<Eigen::VectorXd>* ());
	MOCK_METHOD3(randomizeWeights, void (AbstractRandomGenerator*, double, double));
	MOCK_METHOD1(randomizeDependingOnWeightsSize, void (AbstractRandomGenerator*));
};

#endif
