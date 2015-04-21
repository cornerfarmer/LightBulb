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
	// Inherited:
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

