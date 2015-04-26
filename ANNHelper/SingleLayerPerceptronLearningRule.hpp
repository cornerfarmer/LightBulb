#pragma once

#ifndef _SINGLELAYERPERCEPTRONLEARNINGRULE_H_
#define _SINGLELAYERPERCEPTRONLEARNINGRULE_H_

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The PerceptronLearningRule can only be used to train binary SingleLayerPerceptronNetworks
class SingleLayerPerceptronLearningRule : public AbstractLearningRule
{
private:
public:
	// Improves the given PerceptronNetwork with the help of its teaching stuff
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);
};

#endif