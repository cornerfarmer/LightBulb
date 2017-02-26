#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	class Kernel;
	/**
	 * \brief A binary function can decide between two values
	 * \details The function returns maxValue if the input > 0, otherwise it will return minValue.
	 */
	class BinaryFunction : public AbstractActivationFunction
	{
	private:
		std::unique_ptr<Kernel> binaryAssignKernel;
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
		~BinaryFunction();
		// Inherited:
		double execute(double input) const override;
		double executeDerivation(double input) const override;
		AbstractCloneable* clone() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
		void execute(int layerNr, std::vector<Vector<>>& activations, const std::vector<Vector<>>& netInputs) const;
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::BinaryFunction, LightBulb::AbstractActivationFunction, LightBulb);

#endif