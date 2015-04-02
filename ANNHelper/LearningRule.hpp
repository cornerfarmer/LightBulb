#pragma once

#ifndef _LEARNINGRULE_H_
#define _LEARNINGRULE_H_

#include "NeuralNetwork.hpp"

class LearningRule 
{
private:
public:
	virtual void doLearning(NeuralNetwork &neuralNetwork) = 0;
};

#endif