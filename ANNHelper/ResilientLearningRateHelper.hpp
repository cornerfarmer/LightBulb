#pragma once

#ifndef _RESILIENTLEARNINGRATEHELPER_H_
#define _RESILIENTLEARNINGRATEHELPER_H_

// Library Includes
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>

// Includes
#include "AbstractLearningRule.hpp"

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

	ResilientLearningRateHelperOptions()
	{
		learningRateGrowFac = 1.2f;
		learningRateShrinkFac = 0.5f;
		learningRateMax = 50;
		learningRateMin = 0.000001f;
		learningRateStart = 0.2f;
	}
};


class ResilientLearningRateHelper
{
private:
	std::unique_ptr<std::vector<float>> previousLearningRates;		
	ResilientLearningRateHelperOptions* options;
public:
	float getNextLearningRate(float deltaWeight);	
	void printDebugOutput();
	bool learningHasStopped();
	void initialize(NeuralNetwork &neuralNetwork);	
	ResilientLearningRateHelper(ResilientLearningRateHelperOptions* options_);
	ResilientLearningRateHelper();
};

#endif

