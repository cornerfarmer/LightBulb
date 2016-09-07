#pragma once

#ifndef _RECTIFIERFUNCTION_H_
#define _RECTIFIERFUNCTION_H_

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "IO/UseParentSerialization.hpp"

/**
 * \brief Returns the input if it is greater than 0, otherwise it returns 0.
 * \details Describes: \n \n \f$f(x)=max(0, x)\f$ \n \n
 * Derivative: \n \n \f$ f'(x)={\begin{cases}x&{\mbox{if }}x>0\\0.01x&{\mbox{otherwise}}\end{cases}} \f$
 */
class RectifierFunction : public AbstractActivationFunction
{
private:
	double leakyFac;
public:
	RectifierFunction(double leakyFac_ = 0);
	// Inherited
	double execute(double input) override;
	double executeDerivation(double input) override;
	AbstractActivationFunction* getActivationFunctionCopy() override;
	double getMaximum() override;
	double getMinimum() override;
	bool hasAMaxAndMinimum() override;
};

EMPTY_CHILD_SERIALIZATION(RectifierFunction);

#endif