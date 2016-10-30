#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include <IO/UseParentSerialization.hpp>

namespace LightBulb
{
	/**
	 * \brief A binary function can decide between two values
	 * \details The function returns maxValue if the input > 0, otherwise it will return minValue.
	 */
	class BinaryFunction : public AbstractActivationFunction
	{
	private:
		/**
		 * \brief The minimum value
		 */
		double minValue;
		/**
		 * \brief The maximum value
		 */
		double maxValue;
	public:
		BinaryFunction(double minValue_ = 0, double maxValue_ = 1);
		// Inherited:
		double execute(double input) const override;
		double executeDerivation(double input) const override;
		AbstractCloneable* clone() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
	};
}

EMPTY_CHILD_SERIALIZATION(LightBulb::BinaryFunction, LightBulb);

#endif