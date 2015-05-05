#pragma once

#ifndef _ABSTRACTLEARNINGRULE_H_
#define _ABSTRACTLEARNINGRULE_H_

// Library Includes
#include <vector>

// Forward declarations
class NeuralNetwork;
class Teacher;
class Neuron;
class Edge;
class StandardNeuron;
class AbstractActivationOrder;

struct AbstractLearningRuleOptions
{
	// Sets the maximum iterations per try
	unsigned int maxIterationsPerTry;
	// Sets the maximum number of tries, until the algorithm should abort
	unsigned int maxTries;
	// Sets the highest total error value, when the algorithm should finish successful
	float totalErrorGoal;
	// Sets the lower limit of the random generated weights
	float minRandomWeightValue;
	// Sets the higher limit of the random generated weights
	float maxRandomWeightValue;
	// Sets the minium iterations per try
	unsigned int minIterationsPerTry;
	// Sets the maximum total error value (If a try has after its miniums iterations a greater total error value than the maxTotalErrorValue, skip that try)
	float maxTotalErrorValue;
	// Enable debug output
	bool enableDebugOutput;
	// Sets the debug output interval
	unsigned int debugOutputInterval;
	// Enable offline learning
	bool offlineLearning;

	AbstractLearningRuleOptions()
	{
		maxIterationsPerTry = 10000;
		maxTries = 100;
		totalErrorGoal = 0.01;
		minRandomWeightValue = -0.5f;
		maxRandomWeightValue = 0.5f;
		minIterationsPerTry = 1000;
		maxTotalErrorValue = 2;
		enableDebugOutput = false;
		debugOutputInterval = 1000;	
		offlineLearning = false;
	}
	virtual ~AbstractLearningRuleOptions() {}
};

// A LearningRule is used to improve a NeuralNetwork
class AbstractLearningRule 
{
protected:
	std::unique_ptr<AbstractLearningRuleOptions> options;
	// This method will be called in front of the actual learning algorithm
	virtual void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher) {};
	// This method should calculate the deltaWeight for the actual edge
	virtual float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector) = 0;
	// This method should adjust the weight of the current edge
	virtual void adjustWeight(Edge* edge, float deltaWeight) = 0;
	// Calculate if it is sensible to continue learning
	virtual bool learningHasStopped() = 0;
	// This method could be used to do some work for the current neuron before calculating deltaWeights for every of its edges
	virtual void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector) {};
	// This method should return the used activationOrder
	virtual AbstractActivationOrder* getNewActivationOrder() = 0;
	// Prints a current summary of the status of the learning process
	virtual void printDebugOutput() {};
	// This method should do something like randomizing all weight
	virtual void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher) = 0;

public:	
	AbstractLearningRule(AbstractLearningRuleOptions* options_);
	// Execute the learning process on the given NeuralNetwork
	// If the learning process succeded the method will return true
	bool doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher);


};

#endif