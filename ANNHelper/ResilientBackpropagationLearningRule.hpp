#pragma once

#ifndef _RESILIENTBACKPROPAGATIONLEARNINGRULE_H_
#define _RESILIENTBACKPROPAGATIONLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>

// Includes
#include "AbstractBackpropagationLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;

struct ResilientBackpropagationLearningRuleOptions : AbstractBackpropagationLearningRuleOptions
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

	ResilientBackpropagationLearningRuleOptions()
	{
		learningRateGrowFac = 1.2f;
		learningRateShrinkFac = 0.5f;
		learningRateMax = 50;
		learningRateMin = 0.000001f;
		learningRateStart = 0.2f;
		offlineLearning = true;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class ResilientBackpropagationLearningRule : public AbstractBackpropagationLearningRule
{
private:
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	std::unique_ptr<std::vector<float>> previousLearningRates;		
protected:
	ResilientBackpropagationLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);	
	void printDebugOutput();
	bool learningHasStopped();
	void initializeBackpropagationLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
public:
	ResilientBackpropagationLearningRule(ResilientBackpropagationLearningRuleOptions &options_);
};

#endif

