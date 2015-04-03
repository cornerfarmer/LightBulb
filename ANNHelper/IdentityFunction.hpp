#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

#include "ActivationFunction.hpp"
#include "OutputFunction.hpp"

class IdentityFunction : ActivationFunction, OutputFunction
{
private:
public:
	IdentityFunction();
	float execute(float input);
};

#endif