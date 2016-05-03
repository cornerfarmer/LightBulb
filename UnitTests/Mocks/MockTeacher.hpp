#pragma once

#ifndef _MOCKEVOLUTIONWORLD_H_
#define _MOCKEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Teaching/AbstractTeacher.hpp>
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"

class MockTeacher : public AbstractTeacher
{
public:
	MOCK_METHOD1(addTeachingLesson, void (AbstractTeachingLesson*));
	MOCK_METHOD1(addTestingLesson, void (AbstractTeachingLesson*));
	MOCK_METHOD0(getTeachingLessons, std::vector<std::unique_ptr<AbstractTeachingLesson>>* ());
	MOCK_METHOD0(getTestingLessons, std::vector<std::unique_ptr<AbstractTeachingLesson>>* ());
	MOCK_METHOD2(getTotalError, double (AbstractNeuralNetwork&, AbstractActivationOrder&));
	MOCK_METHOD0(unfold, AbstractTeacher* ());
	MOCK_METHOD0(getMaxTimeStep, int ());
};

#endif
