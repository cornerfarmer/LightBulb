#pragma once

#ifndef _ABSTRACTGRADIENTDECENTALGORITHM_H_
#define _ABSTRACTGRADIENTDECENTALGORITHM_H_

// Library Includes

// Includes
#include "Learning/AbstractLearningRule.hpp"

// Forward declarations
class AbstractNeuralNetwork;

struct AbstractGradientDecentAlgorithmOptions
{
	AbstractGradientDecentAlgorithmOptions()
	{
	}
};


class AbstractGradientDecentAlgorithm
{
private:
	bool initialized;
protected:
	std::unique_ptr<AbstractGradientDecentAlgorithmOptions> options;
	virtual void initializeAlgorithm(AbstractNeuralNetwork &neuralNetwork) = 0;
public:
	AbstractGradientDecentAlgorithm(AbstractGradientDecentAlgorithmOptions* options_);
	// Computes the new learning rate of the given edge from the given gradient
	virtual Eigen::MatrixXd calcDeltaWeight(int layerIndex, Eigen::MatrixXd& gradients) = 0;
	// Print a short debug output (totalLearningRate)
	virtual std::string printDebugOutput() { return ""; };
	// Returns if the learning has stopped
	virtual bool learningHasStopped() = 0;
	// Initializes the ResilientLearningRateHelper
	void initialize(AbstractNeuralNetwork &neuralNetwork);

	bool isInitialized();
};

#endif

