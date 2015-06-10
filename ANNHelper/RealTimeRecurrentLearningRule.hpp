#pragma once

#ifndef _REALTIMERECURRENTLEARNINGRULE_H_
#define _REALTIMERECURRENTLEARNINGRULE_H_

// Library Includes
#include <list>
#include <map>

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;
class AbstractNeuron;
class AbstractNetworkTopology;
class StandardNeuron;

struct RealTimeRecurrentLearningRuleOptions : public AbstractLearningRuleOptions
{	
	// Sets the learning Rate
	float learningRate;	

	RealTimeRecurrentLearningRuleOptions()
	{
		learningRate = 0.45f;
		offlineLearning = false;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class RealTimeRecurrentLearningRule : public AbstractLearningRule
{
private:	
	// Holds all output values in every timestep
	std::vector<std::map<AbstractNeuron*, float>> outputValuesInTime;
	// Holds all netInput values in every timestep
	std::vector<std::map<AbstractNeuron*, float>> netInputValuesInTime;
	// This vector should hold all delta values
	std::map<Edge*, std::list<float>> dynamicSystemCache;
	float getDynamicSystemValueOfEdgeAtTime(Edge* edge, StandardNeuron* neuron, int time);
	AbstractNetworkTopology* currentNetworkTopology;
	int currentTimeStep;
protected:
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	RealTimeRecurrentLearningRuleOptions* getOptions();
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);	
	virtual float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	AbstractActivationOrder* getNewActivationOrder();
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork);
	bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);
	std::vector<std::map<AbstractNeuron*, float>>* getOutputValuesInTime();
	std::vector<std::map<AbstractNeuron*, float>>* getNetInputValuesInTime();
public:
	RealTimeRecurrentLearningRule(RealTimeRecurrentLearningRuleOptions& options_);
};

#endif

