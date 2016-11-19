#pragma once

#ifndef _MOCKTEACHER_H_
#define _MOCKTEACHER_H_

#include "gmock/gmock.h"
#include <Teaching/AbstractTeacher.hpp>
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"

class MockTeacher : public LightBulb::AbstractTeacher
{
public:
	MOCK_METHOD1(addTeachingLesson, void (LightBulb::AbstractTeachingLesson*));
	MOCK_METHOD1(addTestingLesson, void (LightBulb::AbstractTeachingLesson*));
	MOCK_CONST_METHOD0(getTeachingLessons, const std::vector<std::unique_ptr<LightBulb::AbstractTeachingLesson>>& ());
	MOCK_CONST_METHOD0(getTestingLessons, const std::vector<std::unique_ptr<LightBulb::AbstractTeachingLesson>>& ());
	MOCK_CONST_METHOD2(getTotalError, double (LightBulb::AbstractNeuralNetwork&, const LightBulb::AbstractActivationOrder&));
	MOCK_CONST_METHOD2(getTeachingError, double (LightBulb::AbstractNeuralNetwork&, const LightBulb::AbstractActivationOrder&));
	MOCK_CONST_METHOD1(getWeightDecayError, double (LightBulb::AbstractNeuralNetwork&));
	MOCK_CONST_METHOD0(unfold, AbstractTeacher* ());
	MOCK_CONST_METHOD0(getMaxTimeStep, int ());
	MOCK_METHOD0(clearLessons, void ());
};

#endif
