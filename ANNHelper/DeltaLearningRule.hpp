#pragma once

#ifndef _DELTALEARNINGRULE_H_
#define _DELTALEARNINGRULE_H_

// Includes
#include "AbstractDeltaLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks or RBFNetworks
class DeltaLearningRule : public AbstractDeltaLearningRule
{
protected:
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);
	bool learningHasStopped();
public:
	DeltaLearningRule(AbstractLearningRuleOptions &options_);

};

#endif