#pragma once

#ifndef _RECTIFIERFUNCTION_H_
#define _RECTIFIERFUNCTION_H_

// Includes
#include "Function/AbstractActivationFunction.hpp"

// The FermiFunction is a sigmoid function between 0 and 1 which can be adjusted with temperatureParameter
class RectifierFunction : public AbstractActivationFunction
{
private:
	double leakyFac;
public:
	RectifierFunction(double leakyFac_ = 0);
	// Inherited
	double execute(double input);
	double executeDerivation(double input);
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};


#endif