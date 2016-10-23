#pragma once

#ifndef _MOCKTEACHINGLESSON_H_
#define _MOCKTEACHINGLESSON_H_

#include "gmock/gmock.h"
#include <Teaching/AbstractTeachingLesson.hpp>

class MockTeachingLesson : public LightBulb::AbstractTeachingLesson
{
public:
	MOCK_CONST_METHOD1(getTeachingInput, const LightBulb::NeuralNetworkIO<double>& (const LightBulb::AbstractActivationFunction&));
	MOCK_CONST_METHOD0(getTeachingPattern, const std::vector<std::vector<double>>& ());
	MOCK_CONST_METHOD3(getSpecificError, double (LightBulb::AbstractNeuralNetwork&, const LightBulb::AbstractActivationOrder&, bool));
	MOCK_CONST_METHOD0(unfold, AbstractTeachingLesson* ());
	MOCK_CONST_METHOD0(getMaxTimeStep, int ());
};

#endif
