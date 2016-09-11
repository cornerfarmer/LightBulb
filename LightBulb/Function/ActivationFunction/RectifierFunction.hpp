#pragma once

#ifndef _RECTIFIERFUNCTION_H_
#define _RECTIFIERFUNCTION_H_

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "IO/UseParentSerialization.hpp"

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
		double execute(double input) override;
		double executeDerivation(double input) override;
		AbstractActivationFunction* getActivationFunctionCopy() override;
		double getMaximum() override;
		double getMinimum() override;
		bool hasAMaxAndMinimum() override;
		void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>& activations, std::vector<Eigen::VectorXd>& netInputs);
	};
}

EMPTY_CHILD_SERIALIZATION(LightBulb::RectifierFunction, LightBulb);

#endif