#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

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
		double execute(double input) const override;
		void execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>> &activations, const std::vector<Eigen::VectorXd> &netInputs) const override;
		double executeDerivation(double input) const override;
		AbstractCloneable* clone() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::IdentityFunction, LightBulb::AbstractActivationFunction, LightBulb);
#endif