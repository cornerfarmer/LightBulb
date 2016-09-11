#pragma once

#ifndef _MOCKEVOLUTIONWORLD_H_
#define _MOCKEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Teaching/AbstractTeacher.hpp>
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"

class MockTeacher : public LightBulb::AbstractTeacher
{
public:
	MOCK_METHOD1(addTeachingLesson, void (LightBulb::AbstractTeachingLesson*));
	MOCK_METHOD1(addTestingLesson, void (LightBulb::AbstractTeachingLesson*));
	MOCK_METHOD0(getTeachingLessons, std::vector<std::unique_ptr<LightBulb::AbstractTeachingLesson>>* ());
	MOCK_METHOD0(getTestingLessons, std::vector<std::unique_ptr<LightBulb::AbstractTeachingLesson>>* ());
	MOCK_METHOD2(getTotalError, double (LightBulb::AbstractNeuralNetwork&, LightBulb::AbstractActivationOrder&));
	MOCK_METHOD2(getTeachingError, double (LightBulb::AbstractNeuralNetwork&, LightBulb::AbstractActivationOrder&));
	MOCK_METHOD1(getWeightDecayError, double (LightBulb::AbstractNeuralNetwork&));
	MOCK_METHOD0(unfold, AbstractTeacher* ());
	MOCK_METHOD0(getMaxTimeStep, int ());
};

#endif
