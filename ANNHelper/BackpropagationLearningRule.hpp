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
public:
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// This learning method will always success
	void doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif