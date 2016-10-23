#pragma once

#ifndef _MOCKNEURONDESCRIPTION_H_
#define _MOCKNEURONDESCRIPTION_H_

#include "gmock/gmock.h"
#include "NeuronDescription/NeuronDescription.hpp"

class MockNeuronDescription : public LightBulb::NeuronDescription
{
public:
	MOCK_CONST_METHOD0(getActivationFunction, const LightBulb::AbstractActivationFunction& ());
};

#endif
