#pragma once

#ifndef _RESILIENTLEARNINGRATEHELPER_H_
#define _RESILIENTLEARNINGRATEHELPER_H_

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

struct ResilientLearningRateHelperOptions
{	
	// Sets the factor by which the learningRate can grow
	double learningRateGrowFac;
	// Sets the factor by which the learningRate can shrink
	double learningRateShrinkFac;
	// Sets the highest possible learningRate
	double learningRateMax;
	// Sets the lowest possible learningRate
	double learningRateMin;
	// Sets the start value of all learningRates
	double learningRateStart;
	// The lowest total learning rate (if the current value is smaller than this value the learning process will stop)
	double minLearningRate;
	ResilientLearningRateHelperOptions()
	{
		learningRateGrowFac = 1.2f;
		learningRateShrinkFac = 0.5f;
		learningRateMax = 50;
		learningRateMin = 0.000001f;
		learningRateStart = 0.2f;
		minLearningRate = 0;
	}
};


class ResilientLearningRateHelper
{
private:
	// Holds for every edge its previous learning rate
	std::vector<Eigen::MatrixXd> previousLearningRates;
	ResilientLearningRateHelperOptions* options;
	bool initialized;
public:
	ResilientLearningRateHelper(ResilientLearningRateHelperOptions* options_);
	ResilientLearningRateHelper();
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

