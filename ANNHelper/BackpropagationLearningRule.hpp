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

struct BackpropagationLearningRuleOptions : AbstractBackpropagationLearningRuleOptions
{	
	// Sets the momentum, which can improve learning speed
	float momentum;
	// Sets the learning Rate
	float learningRate;	
	BackpropagationLearningRuleOptions()
	{
		momentum = 0.7f;
		learningRate = 0.45f;
		offlineLearning = false;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class BackpropagationLearningRule : public AbstractBackpropagationLearningRule
{
private:	
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Contains all previous deltaWeights (used by the momentum term)
	std::unique_ptr<std::vector<float>> previousDeltaWeights;	
protected:
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	BackpropagationLearningRuleOptions* getOptions();
	float calculateDeltaWeight(Edge* edge, float gradient);
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
public:
	BackpropagationLearningRule(BackpropagationLearningRuleOptions options_);
	BackpropagationLearningRule(BackpropagationLearningRuleOptions* options_);
};

#endif

