#pragma once

#ifndef _MOCKNETWORKTOPOLOGY_H_
#define _MOCKNETWORKTOPOLOGY_H_

#include "gmock/gmock.h"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Random/AbstractRandomGenerator.hpp"

class MockNetworkTopology : public LightBulb::AbstractNetworkTopology
{
public:
	MOCK_CONST_METHOD0(getEdgeCount, int ());
	MOCK_CONST_METHOD0(getInputSize, int ());
	MOCK_CONST_METHOD0(getOutputSize, int ());
	MOCK_METHOD1(setInput, void (const std::vector<double>&));
	MOCK_CONST_METHOD1(getOutput, void (std::vector<double>&));
	MOCK_METHOD0(resetActivation, void ());
	MOCK_METHOD1(copyWeightsFrom, void (const AbstractNetworkTopology&));
	MOCK_CONST_METHOD0(getNeuronCount, int ());
	MOCK_CONST_METHOD1(calculateEuclideanDistance, double (const AbstractNetworkTopology&));
	MOCK_METHOD3(randomizeWeights, void (LightBulb::AbstractRandomGenerator&, double, double));
	MOCK_CONST_METHOD0(getLayerCount, int ());
	MOCK_CONST_METHOD0(getNeuronCountsPerLayer, const std::vector<unsigned>& ());
	MOCK_METHOD1(randomizeDependingOnLayerSize, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD1(refreshNetInputsForLayer, void (int));
	MOCK_METHOD1(refreshActivationsForLayer, void (int));
	MOCK_METHOD0(getAllWeights, std::vector<Eigen::MatrixXd>& ());
	MOCK_CONST_METHOD0(getAllWeights, const std::vector<Eigen::MatrixXd>& ());
	MOCK_CONST_METHOD0(getAllActivations, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& ());
	MOCK_CONST_METHOD0(getAllNetInputs, const std::vector<Eigen::VectorXd>& ());
	MOCK_CONST_METHOD1(getAfferentWeightsPerLayer, Eigen::MatrixXd (int));
	MOCK_METHOD2(setAfferentWeightsPerLayer, void (int, const Eigen::MatrixXd&));
	MOCK_CONST_METHOD1(getEfferentWeightsPerLayer, Eigen::MatrixXd (int));
	MOCK_CONST_METHOD1(getNetInputsPerLayer, Eigen::VectorXd (int));
	MOCK_CONST_METHOD1(getActivationsPerLayer, Eigen::VectorXd (int));
	MOCK_CONST_METHOD2(getEfferentWeightsPerNeuron, Eigen::VectorXd (int, int));
	MOCK_CONST_METHOD2(getBiasWeightOfNeuron, double (int, int));
	MOCK_CONST_METHOD3(getAfferentWeightsPerNeuron, std::vector<double> (int, int, bool));
	MOCK_CONST_METHOD3(getWeight, double (int, int, int));
	MOCK_METHOD4(setWeight, void (int, int, int, double));
	MOCK_CONST_METHOD2(getNetInput, double (int, int));
	MOCK_CONST_METHOD2(getActivation, double (int, int));
	MOCK_CONST_METHOD0(usesBiasNeuron, bool ());
	MOCK_METHOD2(removeNeuron, void (int, int));
	MOCK_METHOD1(addNeuron, void (int));
	MOCK_METHOD3(removeAfferentWeight, void (int, int, int));
	MOCK_METHOD3(existsAfferentWeight, bool (int, int, int));
	MOCK_CONST_METHOD0(clone, AbstractNetworkTopology* ());
	MOCK_CONST_METHOD0(getInnerNeuronDescription, const LightBulb::NeuronDescription& ());
	MOCK_CONST_METHOD0(getOutputNeuronDescription, const LightBulb::NeuronDescription& ());
};

#endif
