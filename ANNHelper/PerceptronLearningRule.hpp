#pragma once

#ifndef _PERCEPTRONLEARNINGRULE_H_
#define _PERCEPTRONLEARNINGRULE_H_

#include "LearningRule.hpp"

class PerceptronLearningRule : LearningRule
{
private:
public:
	void doLearning(NeuralNetwork &neuralNetwork);
};

#endif