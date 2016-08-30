#pragma once

#ifndef _SIMPLEGRADIENTDECENT_H_
#define _SIMPLEGRADIENTDECENT_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientDecentAlgorithm.hpp"

// Forward declarations

struct SimpleGradientDecentOptions : public AbstractGradientDecentAlgorithmOptions
{
	// Sets the weight decay factor, which will be used avoid high weights
	double weightDecayFac;
	// Sets the momentum, which can improve learning speed
	double momentum;
	// Sets the learning Rate
	double learningRate;
	SimpleGradientDecentOptions()
	{
		weightDecayFac = 0;
		momentum = 0.7f;
		learningRate = 0.45f;
	}
};


class SimpleGradientDecent : public AbstractGradientDecentAlgorithm
{
private:
	// Contains all previous deltaWeights (used by the momentum term)
	std::vector<Eigen::MatrixXd> previousDeltaWeights;
	AbstractNeuralNetwork* neuralNetwork;
	SimpleGradientDecentOptions* getOptions();
public:
	SimpleGradientDecent(SimpleGradientDecentOptions& options_);
	SimpleGradientDecent();

	Eigen::MatrixXd calcDeltaWeight(int layerIndex, Eigen::MatrixXd& gradients) override;
	// Print a short debug output (totalLearningRate)
	std::string printDebugOutput();
	// Returns if the learning has stopped
	bool learningHasStopped();
	// Initializes the ResilientLearningRateHelper
	void initializeAlgorithm(AbstractNeuralNetwork &neuralNetwork);
};

#endif

