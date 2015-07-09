#pragma once

#ifndef _RESILIENTLEARNINGRATEHELPER_H_
#define _RESILIENTLEARNINGRATEHELPER_H_

// Library Includes
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>

// Includes
#include "Learning\AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;

struct ResilientLearningRateHelperOptions
{	
	// Sets the factor by which the learningRate can grow
	float learningRateGrowFac;
	// Sets the factor by which the learningRate can shrink
	float learningRateShrinkFac;
	// Sets the highest possible learningRate
	float learningRateMax;
	// Sets the lowest possible learningRate
	float learningRateMin;
	// Sets the start value of all learningRates
	float learningRateStart;
	// The lowest total learning rate (if the current value is smaller than this value the learning process will stop)
	float minLearningRate;
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
	std::map<Edge*, float> previousLearningRates;
	ResilientLearningRateHelperOptions* options;
public:
	ResilientLearningRateHelper(ResilientLearningRateHelperOptions* options_);
	ResilientLearningRateHelper();
	// Computes the new learning rate of the given edge from the given gradient
	float getLearningRate(Edge* edge, float gradient);
	// Print a short debug output (totalLearningRate)
	void printDebugOutput();
	// Returns if the learning has stopped
	bool learningHasStopped();
	// Initializes the ResilientLearningRateHelper
	void initialize(NeuralNetwork &neuralNetwork);	
};

#endif

