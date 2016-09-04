#pragma once

#ifndef _RECTIFIERFUNCTION_H_
#define _RECTIFIERFUNCTION_H_

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "IO/UseParentSerialization.hpp"

// The FermiFunction is a sigmoid function between 0 and 1 which can be adjusted with temperatureParameter
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