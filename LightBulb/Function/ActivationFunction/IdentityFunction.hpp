#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief The IdentityFunction just returns the input without calculating anything
	 * \details Describes: \n \n \f$f(x)=x\f$ \n \n
	 * Derivative: \n \n \f$ f'(x) = 1 \f$
	 */
	class IdentityFunction : public AbstractActivationFunction
	{
	private:
	public:
		// Inherited: 
		double execute(double input) override;
		void execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>> &activations, std::vector<Eigen::VectorXd> &netInputs) override;
		double executeDerivation(double input) override;
		AbstractActivationFunction* getActivationFunctionCopy() override;
		double getMaximum() override;
		double getMinimum() override;
		bool hasAMaxAndMinimum() override;
	};
}

EMPTY_CHILD_SERIALIZATION(LightBulb::IdentityFunction, LightBulb);

#endif