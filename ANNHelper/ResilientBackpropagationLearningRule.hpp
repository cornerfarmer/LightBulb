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

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class ResilientBackpropagationLearningRule : public AbstractBackpropagationLearningRule
{
private:
	// Contains all previous learningRates
	std::unique_ptr<std::vector<float>> previousLearningRates;	
	float learningRateGrowFac;
	float learningRateShrinkFac;
	float learningRateMax;
	float learningRateMin;
	float learningRateStart;
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	void printDebugOutput();
	bool learningHasStopped();
public:
	ResilientBackpropagationLearningRule(BackpropagationLearningRuleOptions options_);
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif

