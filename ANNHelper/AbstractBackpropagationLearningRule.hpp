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

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class AbstractBackpropagationLearningRule : public LearningRule
{
protected:
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
	// Starts the main learning algorithm
	float startAlgorithm(NeuralNetwork &neuralNetwork, Teacher &teacher, ActivationOrder &activationOrder, bool offlineLearning);
	// Adjusts the weights of an edge dependent on its gradient
	virtual void adjustWeight(Edge* edge, float gradient) = 0;
	// Print the debug output
	virtual void printDebugOutput() = 0;
public:
	// Initializes all required values
	AbstractBackpropagationLearningRule(int maxIterationsPerTry_, int maxTries_, float totalErrorGoal_, float minRandomWeightValue_, float maxRandomWeightValue_);
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	virtual bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher) = 0;
};

#endif

