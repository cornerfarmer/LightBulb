#pragma once

#ifndef _PERCEPTRONLEARNINGRULE_H_
#define _PERCEPTRONLEARNINGRULE_H_

// Includes
#include "LearningRule.hpp"

// The PerceptronLearningRule can only be used to train PerceptronNetworks
class PerceptronLearningRule : public LearningRule
{
private:
public:
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// This learning method will always success
	void doLearning(NeuralNetwork &neuralNetwork);
};

#endif