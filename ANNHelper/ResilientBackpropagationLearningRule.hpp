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
#include "ResilientLearningRateHelper.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;

struct ResilientBackpropagationLearningRuleOptions : AbstractBackpropagationLearningRuleOptions, ResilientLearningRateHelperOptions
{	
	ResilientBackpropagationLearningRuleOptions()
	{
		offlineLearning = true;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class ResilientBackpropagationLearningRule : public AbstractBackpropagationLearningRule
{
private:
	std::unique_ptr<ResilientLearningRateHelper> resilientLearningRateHelper;
protected:
	ResilientBackpropagationLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);	
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
public:
	ResilientBackpropagationLearningRule(ResilientBackpropagationLearningRuleOptions &options_);
};

#endif

