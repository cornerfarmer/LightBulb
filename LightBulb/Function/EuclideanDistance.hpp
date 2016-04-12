#pragma once

#ifndef _EUCLIDEANDISTANCEFUNCTION_H_
#define _EUCLIDEANDISTANCEFUNCTION_H_

// Includes
#include "Function/AbstractInputFunction.hpp"
#include "IO/UseParentSerialization.hpp"

//Forward declarations
class Edge;

// The EuclideanDistance calculates the dinstance between the input and the center of a RBF Neuron 
class EuclideanDistance : public AbstractInputFunction
{
private:
public:
	// Calculates sqrt( Σ (output - center)^2 )
	void execute(int layerNr, std::vector<Eigen::VectorXd>& activations, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::MatrixXd>& weights);
	// Inherited:
	AbstractInputFunction* getInputFunctionCopy();
};

EMPTY_CHILD_SERIALIZATION(EuclideanDistance);

#endif
