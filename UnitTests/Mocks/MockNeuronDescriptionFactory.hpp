#pragma once

#ifndef _MOCKNEURONDESCRIPTIONFACTORY_H_
#define _MOCKNEURONDESCRIPTIONFACTORY_H_

#include "gmock/gmock.h"
#include <NeuronDescription/AbstractNeuronDescriptionFactory.hpp>

class MockNeuronDescriptionFactory : public LightBulb::AbstractNeuronDescriptionFactory
{
public:
	MOCK_METHOD0(createInnerNeuronDescription, LightBulb::NeuronDescription* ());
	MOCK_METHOD0(createOutputNeuronDescription, LightBulb::NeuronDescription* ());
	MOCK_CONST_METHOD0(getOutputActivationFunction, const LightBulb::AbstractActivationFunction& ());
	MOCK_CONST_METHOD0(getInnerActivationFunction, const LightBulb::AbstractActivationFunction& ());
	AbstractNeuronDescriptionFactory* getCopy() const override { return new MockNeuronDescriptionFactory(); };
};

#endif
