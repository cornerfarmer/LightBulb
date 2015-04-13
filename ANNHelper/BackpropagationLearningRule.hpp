#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULE_H_
#define _BACKPROPAGATIONLEARNINGRULE_H_

// Includes
#include "LearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class BackpropagationLearningRule : public LearningRule
{
private:
	// Sets the maximum iterations per try
	int maxIterationsPerTry;
	// Sets the maximum number of tries, until the algorithm should abort
	int maxTries;
	// Sets the highest total error value, when the algorithm should finish successful
	float totalErrorGoal;
	// Sets the learning Rate
	float learningRate;
	// Sets the lower limit of the random generated weights
	float minRandomWeightValue;
	// Sets the higher limit of the random generated weights
	float maxRandomWeightValue;
public:
	// Initializes all required values
	BackpropagationLearningRule(int maxIterationsPerTry_, int maxTries_, float totalErrorGoal_, float learningRate_, float minRandomWeightValue_, float maxRandomWeightValue_);
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif

