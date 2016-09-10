#pragma once

#ifndef _EXPONENTIALSHRINKFUNCTION_H_
#define _EXPONENTIALSHRINKFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/ShrinkFunction/AbstractShrinkFunction.hpp"

namespace LightBulb
{
	// Describes a value which shrinks exponential
	class ExponentialShrinkFunction : public AbstractShrinkFunction
	{
	private:
		double speedFactor;
	public:
		ExponentialShrinkFunction(double startValue_, double minValue_, double speedFactor_);
		// Inherited:	
		double execute(double time) override;
		AbstractShrinkFunction* getShrinkFunctionCopy() override;
	};
}

#endif