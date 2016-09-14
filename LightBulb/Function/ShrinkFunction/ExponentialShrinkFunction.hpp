#pragma once

#ifndef _EXPONENTIALSHRINKFUNCTION_H_
#define _EXPONENTIALSHRINKFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/ShrinkFunction/AbstractShrinkFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a value which shrinks exponential.
	 * \details Describes: \n \n
	 * \f$ f(time)= startValue * e^{-\frac{time}{speedFactor}} + minValue \f$
	 */
	class ExponentialShrinkFunction : public AbstractShrinkFunction
	{
	private:
		/**
		 * \brief The factor which determines how fast the speed changes.
		 */
		double speedFactor;
	public:
		/**
		 * \brief Creates a ExponentialShrinkFunction
		 * \param startValue_ The starting value.
		 * \param minValue_ The lowest possible value.
		 * \param speedFactor_ The factor which determines how fast the speed changes.
		 */
		ExponentialShrinkFunction(double startValue_, double minValue_, double speedFactor_);
		// Inherited:	
		double execute(double time) override;
		AbstractShrinkFunction* getShrinkFunctionCopy() override;
	};
}

#endif