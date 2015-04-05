#pragma once

#ifndef _SINGLELAYERPERCEPTRONLEARNINGRULE_H_
#define _SINGLELAYERPERCEPTRONLEARNINGRULE_H_

// Includes
#include "LearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The PerceptronLearningRule can only be used to train binary SinglePerceptronNetworks
class SingleLayerPerceptronLearningRule : public LearningRule
{
private:
public:
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// This learning method will always success
	void doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif