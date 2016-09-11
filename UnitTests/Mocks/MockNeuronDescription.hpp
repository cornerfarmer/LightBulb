#pragma once

#ifndef _MOCKNEURONDESCRIPTION_H_
#define _MOCKNEURONDESCRIPTION_H_

#include "gmock/gmock.h"
#include "NeuronDescription/NeuronDescription.hpp"

class MockNeuronDescription : public LightBulb::NeuronDescription
{
public:
	MOCK_METHOD0(getActivationFunction, LightBulb::AbstractActivationFunction* ());
};

#endif
