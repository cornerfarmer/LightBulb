#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "Function/OutputFunction/AbstractOutputFunction.hpp"
#include "IO/UseParentSerialization.hpp"

// The IdentityFunction just returns the input without calculating anything
class IdentityFunction : public AbstractActivationFunction, public AbstractOutputFunction
{
private:
public:
	// Inherited: 
	double execute(double input) override;
	void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> &activations, std::vector<Eigen::VectorXd> &netInputs) override;
	double executeDerivation(double input) override;
	AbstractOutputFunction* getOutputFunctionCopy() override;
	AbstractActivationFunction* getActivationFunctionCopy() override;
	double getMaximum() override;
	double getMinimum() override;
	bool hasAMaxAndMinimum() override;
};

EMPTY_CHILD_SERIALIZATION(IdentityFunction);

#endif