#pragma once

#ifndef _GAUSSIANRBFFUNCTION_H_
#define _GAUSSIANRBFFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "Function/NeighborhoodFunction/AbstractNeighborhoodFunction.hpp"

namespace LightBulb
{
	// TODO: Refactor
	class GaussianRBFFunction : public AbstractActivationFunction, public AbstractNeighborhoodFunction
	{
	private:
		Eigen::VectorXd* widths;
	public:
		GaussianRBFFunction(Eigen::VectorXd* widths_);
		// Inherited:
		void execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, const std::vector<Eigen::VectorXd>& netInputs) const override;
		double execute(double input) const override;
		double executeDerivation(double input) const override;
		AbstractActivationFunction* getActivationFunctionCopy() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
		double execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance) const override;
		AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy() const override;
	};
}

#include "IO/GaussianRBFFunctionIO.hpp"

#endif