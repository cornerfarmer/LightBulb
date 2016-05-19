#pragma once

#ifndef _ABSTRACTACTIVATIONFUNCTION_H_
#define _ABSTRACTACTIVATIONFUNCTION_H_

// Library includes
#include <vector>
#include <EigenSrc/Cholesky>
#include <memory>

// Forward declaration
class AbstractThreshold;


// This abstract class describes a function, which can calculate the activation of a neuron
class AbstractActivationFunction
{
private:
public:
	virtual ~AbstractActivationFunction() {}
	// Calculate the activation from the given input
	virtual void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> &activations, std::vector<Eigen::VectorXd> &netInputs);

	virtual double execute(double input) = 0;
	// Calculate the derivated activation from the given input
	virtual double executeDerivation(double input) = 0;
	// Calculate the derivated activation from the given input
	virtual Eigen::VectorXd executeDerivation(Eigen::VectorXd input);
	// Create a copy of the object
	virtual AbstractActivationFunction* getActivationFunctionCopy() = 0;
	// Returns the maximum value of this function
	virtual double getMaximum() = 0;
	// Returns the minimum value of this function
	virtual double getMinimum() = 0;
	// Returns if has a minimum/maximum value
	virtual bool hasAMaxAndMinimum() = 0;
};

#endif