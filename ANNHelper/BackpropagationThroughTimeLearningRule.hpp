#pragma once

#ifndef _BACKPROPAGATIONTHROUGHTIMELEARNINGRULE_H_
#define _BACKPROPAGATIONTHROUGHTIMELEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "BackpropagationLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;

struct BackpropagationThroughTimeLearningRuleOptions : BackpropagationLearningRuleOptions
{	
	// 
	unsigned int maxTimeSteps;
	BackpropagationThroughTimeLearningRuleOptions()
	{
		maxTimeSteps = 1;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class BackpropagationThroughTimeLearningRule : public BackpropagationLearningRule
{
private:	
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// This vector should hold all delta weight sums
	std::vector<float> deltaWeightSums;
	// This variable contains the original network which is not unfolded
	NeuralNetwork* originalNeuralNetwork;
protected:
	// Returns our current options in form of a BackpropagationThroughTimeLearningRuleOptions object
	BackpropagationThroughTimeLearningRuleOptions* getOptions();
	// Inherited:
	void doCalculationAfterTeachingLesson(NeuralNetwork &neuralNetwork);
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
	NeuralNetwork* initializeNeuralNetwork(NeuralNetwork &neuralNetwork);
	void doCalculationAfterLearningProcess(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork);
public:
	BackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_);
};

#endif

