#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "IO/UseParentSerialization.hpp"

//Forward declarations
class Edge;

// The WeightedSumFunction uses the weighted sum to calculate the input ;) 
class WeightedSumFunction : public AbstractInputFunction
{
private:
public:
	// Calculates Σ output * weight
	void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> &activations, std::vector<Eigen::VectorXd> &netInputs, std::vector<Eigen::MatrixXd> &weights);
	AbstractInputFunction* getInputFunctionCopy();
};

EMPTY_CHILD_SERIALIZATION(WeightedSumFunction);

#endif
