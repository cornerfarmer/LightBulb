#pragma once

#ifndef _MOCKNEURONDESCRIPTION_H_
#define _MOCKNEURONDESCRIPTION_H_

#include "gmock/gmock.h"
#include "Neuron/NeuronDescription.hpp"

class MockNeuronDescription : public NeuronDescription
{
public:
	MOCK_METHOD0(getActivationFunction, AbstractActivationFunction* ());
};

#endif
