#pragma once

#ifndef _ABSTRACTINPUTFUNCTION_H_
#define _ABSTRACTINPUTFUNCTION_H_

// Includes
#include <list>
#include <memory>
#include "EigenSrc/Dense"
#include <vector>

// Forward declarations
class Edge;
class AbstractThreshold;
class AbstractNeuron;

// An InputFunction calculates one input value from the output of all previous neurons
class AbstractInputFunction
{
private:
public:
	virtual ~AbstractInputFunction() {}
	// Calculate the one value from all given input edges and the additional input.
	// The neuronOutputCache can be used do use a cached activation instead of the real/current one.
	virtual void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> &activations, std::vector<Eigen::VectorXd> &netInputs, std::vector<Eigen::MatrixXd> &weights) = 0;
	// Create a copy of the object
	virtual AbstractInputFunction* getInputFunctionCopy() = 0;
};

#endif