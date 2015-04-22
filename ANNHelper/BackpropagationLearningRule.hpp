#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULE_H_
#define _BACKPROPAGATIONLEARNINGRULE_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractBackpropagationLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class BackpropagationLearningRule : public AbstractBackpropagationLearningRule
{
private:
	// Sets the learning Rate
	float learningRate;	
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Sets the momentum, which can improve learning speed
	float momentum;
	// Is set, if offline learning should be used
	bool offlineLearning;
	// Contains all previous deltaWeights (used by the momentum term)
	std::unique_ptr<std::vector<float>> previousDeltaWeights;	
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
public:
	BackpropagationLearningRule(BackpropagationLearningRuleOptions options_ ,float learningRate_, float momentum_, bool offlineLearning_);
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif

