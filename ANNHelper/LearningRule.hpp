#pragma once

#ifndef _LEARNINGRULE_H_
#define _LEARNINGRULE_H_

class NeuralNetwork;

class LearningRule 
{
private:
public:
	virtual void doLearning(NeuralNetwork &neuralNetwork) = 0;
};

#endif