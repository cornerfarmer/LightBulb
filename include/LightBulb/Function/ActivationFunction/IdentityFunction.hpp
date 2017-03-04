#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	class Kernel;
	/**
	 * \brief The IdentityFunction just returns the input without calculating anything
	 * \details Describes: \n \n \f$f(x)=x\f$ \n \n
	 * Derivative: \n \n \f$ f'(x) = 1 \f$
	 */
	class IdentityFunction : public AbstractActivationFunction
	{
	private:
		std::unique_ptr<Kernel> identityDerivAssignKernel;
	public:
		IdentityFunction();
		~IdentityFunction();
		// Inherited: 
		double execute(double input) const override;
		void execute(int layerNr, std::vector<Vector<>> &activations, const std::vector<Vector<>> &netInputs) const override;
		void executeDerivation(const Vector<>& input, Vector<>& derivation) const;
		double executeDerivation(double input) const override;
		AbstractCloneable* clone() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::IdentityFunction, LightBulb::AbstractActivationFunction, LightBulb);
#endif