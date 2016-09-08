#pragma once

#ifndef _EUCLIDEANDISTANCEFUNCTION_H_
#define _EUCLIDEANDISTANCEFUNCTION_H_

// Includes
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "IO/UseParentSerialization.hpp"

//Forward declarations

/**
 * \brief The EuclideanDistance calculates the distance between the input and the center of a RBF Neuron (weights)
 * \details Describes: \n \n \f$o=\sqrt{\sum{(\vec{w} - \vec{a})^2}}\f$ \n \n
 */
class EuclideanDistance : public AbstractInputFunction
{
private:
public:
	// Inherited:
	void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>& activations, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::MatrixXd>& weights) override;
	AbstractInputFunction* getInputFunctionCopy() override;
};

EMPTY_CHILD_SERIALIZATION(EuclideanDistance);

#endif
