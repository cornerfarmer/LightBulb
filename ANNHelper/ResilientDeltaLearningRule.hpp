#pragma once

#ifndef _RESILIENTDELTALEARNINGRULE_H_
#define _RESILIENTDELTALEARNINGRULE_H_

// Includes
#include "DeltaLearningRule.hpp"
#include "ResilientLearningRateHelper.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct ResilientDeltaLearningRuleOptions : AbstractLearningRuleOptions, ResilientLearningRateHelperOptions
{	
	ResilientDeltaLearningRuleOptions()
	{
		offlineLearning = true;
	}
};


// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks or RBFNetworks
class ResilientDeltaLearningRule : public AbstractDeltaLearningRule
{
private:
	std::unique_ptr<ResilientLearningRateHelper> resilientLearningRateHelper;
protected:
	ResilientDeltaLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);	
	void printDebugOutput();
	bool learningHasStopped();
	void initializeDeltaLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
public:
	ResilientDeltaLearningRule(ResilientDeltaLearningRuleOptions &options_);

};

#endif