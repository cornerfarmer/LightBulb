#pragma once

#ifndef _PERCEPTRONLEARNINGRULE_H_
#define _PERCEPTRONLEARNINGRULE_H_

// Includes
#include "LearningRule.hpp"

// The PerceptronLearningRule can only be used to train PerceptronNetworks
class PerceptronLearningRule : LearningRule
{
private:
public:
	void doLearning(NeuralNetwork &neuralNetwork);
};

#endif