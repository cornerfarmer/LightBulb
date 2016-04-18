#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "Function/AbstractActivationFunction.hpp"
#include "Function/AbstractOutputFunction.hpp"
#include "IO/UseParentSerialization.hpp"

// The IdentityFunction just returns the input without calculating anything
class IdentityFunction : public AbstractActivationFunction, public AbstractOutputFunction
{
private:
public:
	// Inherited: 
	double execute(double input);
	void execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>> &activations, std::vector<Eigen::VectorXd> &netInputs);
	double executeDerivation(double input);
	AbstractOutputFunction* getOutputFunctionCopy();
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};

EMPTY_CHILD_SERIALIZATION(IdentityFunction);

#endif