#pragma once

#ifndef _SCHMIDHUBERLEARNINGRULE_H_
#define _SCHMIDHUBERLEARNINGRULE_H_

// Library Includes
#include <list>
#include <map>

// Includes
#include "AbstractLearningRule.hpp"
#include "TruncatedBackpropagationThroughTimeLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;
class AbstractNeuron;
class AbstractNetworkTopology;
class StandardNeuron;

struct SchmidhuberLearningRuleOptions : public AbstractLearningRuleOptions
{	
	// Sets the learning Rate
	float learningRate;
	SchmidhuberLearningRuleOptions()
	{
		learningRate = 0.45f;
		offlineLearning = false;
	}
};

// The SchmidhuberLearningRule combines RTRL and BPTT to train recurrent networks faster
class SchmidhuberLearningRule : public AbstractLearningRule
{
private:	
	// Holds all output values in every timestep
	std::vector<std::map<AbstractNeuron*, float>> outputValuesInTime;
	// Holds all netInput values in every timestep
	std::vector<std::map<AbstractNeuron*, float>> netInputValuesInTime;
	// This vector should hold all delta values in all timesteps (The boolean value holds the information, if the deltavalue is valid)
	std::map<AbstractNeuron*, std::vector<std::pair<float, bool>>> deltaVectorOutputLayer;
	// Caches all current dynamic system values
	std::unique_ptr<std::map<StandardNeuron*, std::map<Edge*, float>>> currentDynamicSystemValues;
	// Caches all previous dynamic system values 
	std::unique_ptr<std::map<StandardNeuron*, std::map<Edge*, float>>> oldDynamicSystemValues;
	// Holds the size of the current computation block
	int currentBlockSize;
	// Holds the start of the current computation block
	int currentBlockStart;
	// Holds all previous gradients
	std::map<Edge*, float> lastGradients;
	// Computes the gamma value of a neuron in a given timestep depending on another neuron
	float getGammaOfNeuronsInTime(StandardNeuron* neuronj, StandardNeuron* neuronk, int time);
	// Computes the dynamic system value of a the depending on a neuron (RTRL part of the algorithm)
	float getDynamicSystemValue(StandardNeuron* neuron, Edge* edge);
	// Holds the current network topology
	AbstractNetworkTopology* currentNetworkTopology;
	// Returns the delta vector/value of a neuron at a given timestep (BTTP part of the algorithm)
	float getDeltaVectorOfNeuronInTime(StandardNeuron* neuron, int time, ErrorMap_t* errormap);

protected:
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	SchmidhuberLearningRuleOptions* getOptions();
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);	
	virtual float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork);
	bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);
	std::vector<std::map<AbstractNeuron*, float>>* getOutputValuesInTime();
	std::vector<std::map<AbstractNeuron*, float>>* getNetInputValuesInTime();
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
public:
	SchmidhuberLearningRule(SchmidhuberLearningRuleOptions& options_);
};

#endif

