#pragma once

#ifndef _MOCKEVOLUTIONOBJECT_H_
#define _MOCKEVOLUTIONOBJECT_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractEvolutionObject.hpp>
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"

class MockEvolutionObject : public LightBulb::AbstractEvolutionObject
{
public:
	MOCK_METHOD1(copyPropertiesFrom, void (AbstractEvolutionObject&));
	MOCK_METHOD0(getNeuralNetwork, LightBulb::AbstractNeuralNetwork& ());
	MOCK_METHOD0(getMutationStrength, std::vector<double>& ());
	MOCK_METHOD1(setMutationStrength, void (const std::vector<double>&));
	MOCK_METHOD0(doNNCalculation, void ());
	MOCK_METHOD0(resetNN, void ());
	MOCK_CONST_METHOD1(clone, AbstractEvolutionObject* (bool));
	MOCK_METHOD1(setEvolutionSource, void (const LightBulb::EvolutionSource&));
	MOCK_METHOD2(removeNeuron, void (int, int));
	MOCK_METHOD1(addNeuron, void (int));
};

#endif
