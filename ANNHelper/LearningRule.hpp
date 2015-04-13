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
	// If the learning process succeded the method will return true
	virtual bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher) = 0;
};

#endif