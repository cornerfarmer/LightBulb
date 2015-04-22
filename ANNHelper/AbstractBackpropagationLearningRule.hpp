#pragma once

#ifndef _ABSTRACTBACKPROPAGATIONLEARNINGRULE_H_
#define _ABSTRACTBACKPROPAGATIONLEARNINGRULE_H_

// Includes
#include "LearningRule.hpp"

#define DEBUGOUTPUTINTERVAL 1000

// Forward declarations
class NeuralNetwork;
class Teacher;
class ActivationOrder;
class Edge;

struct BackpropagationLearningRuleOptions
{
	// Sets the maximum iterations per try
	int maxIterationsPerTry;
	// Sets the maximum number of tries, until the algorithm should abort
	int maxTries;
	// Sets the highest total error value, when the algorithm should finish successful
	float totalErrorGoal;
	// Sets the lower limit of the random generated weights
	float minRandomWeightValue;
	// Sets the higher limit of the random generated weights
	float maxRandomWeightValue;
	// Sets the minium iterations per try
	int minIterationsPerTry;
	// Sets the maximum total error value (If a try has after its miniums iterations a greater total error value than the maxTotalErrorValue, skip that try)
	int maxTotalErrorValue;
	// Enable debug output
	bool enableDebugOutput;
	// Sets the debug output interval
	int debugOutputInterval;
	// Sets the factor of the flat spot elimination, which will increase learning speed when having big weights
	float flatSpotEliminationFac;
	// Sets the weight decay factor, which will be used avoid high weights
	float weightDecayFac;

	BackpropagationLearningRuleOptions()
	{
		maxIterationsPerTry = 100000;
		maxTries = 100;
		totalErrorGoal = 1;
		minRandomWeightValue = -0.5f;
		maxRandomWeightValue = 0.5f;
		minIterationsPerTry = 1000;
		maxTotalErrorValue = 2;
		enableDebugOutput = false;
		debugOutputInterval = 1000;
		flatSpotEliminationFac = 0.1;
		weightDecayFac = 0.02;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class AbstractBackpropagationLearningRule : public LearningRule
{
protected:	
	BackpropagationLearningRuleOptions options;
	// Starts the main learning algorithm
	float startAlgorithm(NeuralNetwork &neuralNetwork, Teacher &teacher, ActivationOrder &activationOrder, bool offlineLearning);
	// Adjusts the weights of an edge dependent on its gradient
	virtual void adjustWeight(Edge* edge, float gradient) = 0;
	// Prints a current summary of the status of the learning process
	virtual void printDebugOutput() = 0;
	// Calculate if it is sensible to continue learning
	virtual bool learningHasStopped() = 0;
public:
	// Initializes all required values
	AbstractBackpropagationLearningRule(BackpropagationLearningRuleOptions options_);
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	virtual bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher) = 0;
};

#endif

