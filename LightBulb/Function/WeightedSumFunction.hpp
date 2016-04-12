#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "Function/AbstractInputFunction.hpp"

//Forward declarations
class Edge;

// The WeightedSumFunction uses the weighted sum to calculate the input ;) 
class WeightedSumFunction : public AbstractInputFunction
{
private:
public:
	// Calculates Σ output * weight
	void execute(int layerNr, std::vector<Eigen::VectorXd> &activations, std::vector<Eigen::VectorXd> &netInputs, std::vector<Eigen::MatrixXd> &weights);
	AbstractInputFunction* getInputFunctionCopy();
};

#include "IO/WeightedSumFunctionIO.hpp"

#endif
