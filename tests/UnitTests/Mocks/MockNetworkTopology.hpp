#pragma once

#ifndef _MOCKNETWORKTOPOLOGY_H_
#define _MOCKNETWORKTOPOLOGY_H_

#include "gmock/gmock.h"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/ActivationOrder/AbstractActivationOrder.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

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
	MOCK_METHOD1(refreshActivationsForLayer, void (int));
	MOCK_METHOD0(getAllWeights, std::vector<LightBulb::Matrix<>>& ());
	MOCK_CONST_METHOD0(getAllWeights, const std::vector<LightBulb::Matrix<>>& ());
	MOCK_CONST_METHOD0(getAllActivations, const std::vector<LightBulb::Vector<>>& ());
	MOCK_CONST_METHOD0(getAllNetInputs, const std::vector<LightBulb::Vector<>>& ());
	MOCK_CONST_METHOD1(getAfferentWeightsPerLayer, LightBulb::Matrix<>(int));
	MOCK_METHOD2(setAfferentWeightsPerLayer, void (int, const LightBulb::Matrix<>&));
	MOCK_CONST_METHOD1(getEfferentWeightsPerLayer, LightBulb::Matrix<>(int));
	MOCK_CONST_METHOD1(getNetInputsPerLayer, LightBulb::Vector<>(int));
	MOCK_CONST_METHOD1(getActivationsPerLayer, LightBulb::Vector<>(int));
	MOCK_CONST_METHOD2(getEfferentWeightsPerNeuron, LightBulb::Vector<>(int, int));
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
	MOCK_CONST_METHOD0(getDefaultActivationOrder, const LightBulb::AbstractActivationOrder& ());
	MOCK_METHOD1(setCalculatorType, void (const LightBulb::CalculatorType&));
	MOCK_METHOD2(refreshNetInputsForLayer, void (int, const LightBulb::Vector<>*));
};

#endif
