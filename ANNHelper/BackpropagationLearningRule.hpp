#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULE_H_
#define _BACKPROPAGATIONLEARNINGRULE_H_

// Includes
#include "AbstractBackpropagationLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class ActivationOrder;
class Edge;

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class BackpropagationLearningRule : public AbstractBackpropagationLearningRule
{
private:
	// Sets the learning Rate
	float learningRate;	
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
public:
	BackpropagationLearningRule(int maxIterationsPerTry_, int maxTries_, float totalErrorGoal_, float minRandomWeightValue_, float maxRandomWeightValue_, float learningRate_);
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif

