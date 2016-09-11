#pragma once

#ifndef _MOCKTEACHINGLESSON_H_
#define _MOCKTEACHINGLESSON_H_

#include "gmock/gmock.h"
#include <Teaching/AbstractTeachingLesson.hpp>

class MockTeachingLesson : public LightBulb::AbstractTeachingLesson
{
public:
	MOCK_METHOD1(getTeachingInput, LightBulb::NeuralNetworkIO<double>* (LightBulb::AbstractActivationFunction*));
	MOCK_METHOD0(getTeachingPattern, std::vector<std::vector<double>>* ());
	MOCK_METHOD3(getSpecificError, double (LightBulb::AbstractNeuralNetwork&, LightBulb::AbstractActivationOrder&, bool));
	MOCK_METHOD0(unfold, AbstractTeachingLesson* ());
	MOCK_METHOD0(getMaxTimeStep, int ());
};

#endif
