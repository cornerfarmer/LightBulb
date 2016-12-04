#pragma once

#ifndef _MOCKINDIVIDUAL_H_
#define _MOCKINDIVIDUAL_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractIndividual.hpp>
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"

class MockIndividual : public LightBulb::AbstractIndividual
{
public:
	MOCK_METHOD1(copyPropertiesFrom, void (AbstractIndividual&));
	MOCK_METHOD0(getNeuralNetwork, LightBulb::AbstractNeuralNetwork& ());
	MOCK_METHOD0(getMutationStrength, std::vector<double>& ());
	MOCK_METHOD1(setMutationStrength, void (const std::vector<double>&));
	MOCK_METHOD0(doNNCalculation, void ());
	MOCK_METHOD0(resetNN, void ());
	MOCK_CONST_METHOD1(clone, AbstractIndividual* (bool));
	MOCK_METHOD1(setEvolutionSource, void (const LightBulb::EvolutionSource&));
	MOCK_METHOD2(removeNeuron, void (int, int));
	MOCK_METHOD1(addNeuron, void (int));
};

#endif
