#pragma once

#ifndef _DELTALEARNINGRULE_H_
#define _DELTALEARNINGRULE_H_

// Includes
#include "LearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks
class DeltaLearningRule : public LearningRule
{
private:
public:
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif