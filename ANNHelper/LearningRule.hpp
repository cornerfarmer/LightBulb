#pragma once

#ifndef _LEARNINGRULE_H_
#define _LEARNINGRULE_H_

// Forward declarations
class NeuralNetwork;
class Teacher;

// A LearningRule is used to improve a NeuralNetwork
class LearningRule 
{
private:
public:
	// Execute the learning process on the given NeuralNetwork
	virtual void doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher) = 0;
};

#endif