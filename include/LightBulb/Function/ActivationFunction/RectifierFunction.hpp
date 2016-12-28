#pragma once

#ifndef _RECTIFIERFUNCTION_H_
#define _RECTIFIERFUNCTION_H_

// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief Returns the input if it is greater than 0, otherwise it returns 0.
	 * \details Describes: \n \n \f$ f(x)={\begin{cases}x&{\mbox{if }}x>0\\ \alpha*x&{\mbox{otherwise}}\end{cases}} \f$ \n \n
	 * Derivative: \n \n \f$ f'(x)={\begin{cases}1&{\mbox{if }}x>0\\ \alpha&{\mbox{otherwise}}\end{cases}} \f$
	 */
	class RectifierFunction : public AbstractActivationFunction
	{
	private:
		/**
		 * \brief The alpha factor which influnces the output for negative input
		 */
		double leakyFac;
	public:
		/**
		 * \brief Creates the RectifierFunction
		 * \param leakyFac_ The alpha factor which influnces the output for negative input
		 */
		RectifierFunction(double leakyFac_ = 0);
		// Inherited
		double execute(double input) const override;
		double executeDerivation(double input) const override;
		AbstractCloneable* clone() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
		void execute(int layerNr, std::vector<Vector> &activations, const std::vector<Vector> &netInputs) const override;
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::RectifierFunction, LightBulb::AbstractActivationFunction, LightBulb);

#endif