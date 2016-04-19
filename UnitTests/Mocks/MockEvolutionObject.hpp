#pragma once

#ifndef _MOCKEVOLUTIONOBJECT_H_
#define _MOCKEVOLUTIONOBJECT_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractEvolutionObject.hpp>

class MockEvolutionObject : public AbstractEvolutionObject
{
public:
	MOCK_METHOD0(getNeuralNetwork, NeuralNetwork* ());
	MOCK_METHOD0(getMutationStrength, std::vector<double>* ());
	MOCK_METHOD1(setMutationStrength, void (std::vector<double>*));
	MOCK_METHOD0(doNNCalculation, void ());
	MOCK_METHOD0(resetNN, void ());
	MOCK_METHOD1(clone, AbstractEvolutionObject* (bool));
	MOCK_METHOD1(copyPropertiesFrom, void (AbstractEvolutionObject*));
};

#endif
