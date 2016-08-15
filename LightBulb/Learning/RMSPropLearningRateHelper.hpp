#pragma once

#ifndef _RMSPROPLEARNINGRATEHELPEROPTIONS_H_
#define _RMSPROPLEARNINGRATEHELPEROPTIONS_H_

// Library Includes
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

// Includes
#include "Learning/AbstractLearningRule.hpp"

// Forward declarations
class Teacher;
class Edge;
class AbstractNeuralNetwork;

struct RMSPropLearningRateHelperOptions
{	
	// Sets the factor by which the learningRate can grow
	double decayFac;
	double learningRate;
	double minSquaredGradient;
	RMSPropLearningRateHelperOptions()
	{
		decayFac = 0.9;
		learningRate = 0.25;
		minSquaredGradient = 0.01;
	}
};


class RMSPropLearningRateHelper
{
private:
	// Holds for every edge its previous learning rate
	std::vector<Eigen::MatrixXd> prevDeltaWeights;
	RMSPropLearningRateHelperOptions* options;
	bool initialized;
public:
	RMSPropLearningRateHelper(RMSPropLearningRateHelperOptions* options_);
	RMSPropLearningRateHelper();
	// Computes the new learning rate of the given edge from the given gradient
	Eigen::MatrixXd getLearningRate(int layerIndex, Eigen::MatrixXd& gradients);
	// Print a short debug output (totalLearningRate)
	std::string printDebugOutput();
	// Returns if the learning has stopped
	bool learningHasStopped();
	// Initializes the ResilientLearningRateHelper
	void initialize(AbstractNeuralNetwork &neuralNetwork);

	bool isInitialized();
};

#endif

