#pragma once

#ifndef _MOCKTEACHINGLESSON_H_
#define _MOCKTEACHINGLESSON_H_

#include "gmock/gmock.h"
#include <Teaching/AbstractTeachingLesson.hpp>

class MockTeachingLesson : public AbstractTeachingLesson
{
public:
	MOCK_METHOD2(getSpecificError, double (AbstractNeuralNetwork&, AbstractActivationOrder&));
	MOCK_METHOD1(getTeachingInput, NeuralNetworkIO<double>* (AbstractActivationFunction*));
	MOCK_METHOD0(getTeachingPattern, std::vector<std::vector<double>>* ());
	MOCK_METHOD0(unfold, AbstractTeachingLesson* ());
	MOCK_METHOD0(getMaxTimeStep, int ());
};

#endif
