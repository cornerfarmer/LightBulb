#pragma once

#ifndef _RBFINTERPOLATIONLEARNINGRULE_H_
#define _RBFINTERPOLATIONLEARNINGRULE_H_

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks
class RBFInterpolationLearningRule : public AbstractLearningRule
{
private:
public:
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif