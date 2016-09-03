#pragma once

#ifndef _MOCKNEURONDESCRIPTIONFACTORY_H_
#define _MOCKNEURONDESCRIPTIONFACTORY_H_

#include "gmock/gmock.h"
#include <NeuronDescription/AbstractNeuronDescriptionFactory.hpp>

class MockNeuronDescriptionFactory : public AbstractNeuronDescriptionFactory
{
public:
	MOCK_METHOD0(createInnerNeuronDescription, NeuronDescription* ());
	MOCK_METHOD0(createOutputNeuronDescription, NeuronDescription* ());
	MOCK_METHOD0(getOutputActivationFunction, AbstractActivationFunction* ());
	MOCK_METHOD0(getInnerActivationFunction, AbstractActivationFunction* ());

	AbstractNeuronDescriptionFactory* getCopy() { return new MockNeuronDescriptionFactory(); };
};

#endif
