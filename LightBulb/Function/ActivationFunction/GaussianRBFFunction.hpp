#pragma once

#ifndef _GAUSSIANRBFFUNCTION_H_
#define _GAUSSIANRBFFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "Function/NeighborhoodFunction/AbstractNeighborhoodFunction.hpp"

// TODO: Refactor
class GaussianRBFFunction : public AbstractActivationFunction, public AbstractNeighborhoodFunction
{
private:
	Eigen::VectorXd* widths;
public:
	GaussianRBFFunction(Eigen::VectorXd* widths_);
	// Inherited:
	void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>& activations, std::vector<Eigen::VectorXd>& netInputs) override;
	double execute(double input) override;
	double executeDerivation(double input) override;
	AbstractActivationFunction* getActivationFunctionCopy() override;
	double getMaximum() override;
	double getMinimum() override;
	bool hasAMaxAndMinimum() override;
	double execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance) override;
	AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy() override;
};

#include "IO/GaussianRBFFunctionIO.hpp"

#endif