#pragma once

#ifndef _REALTIMERECURRENTLEARNINGRULE_H_
#define _REALTIMERECURRENTLEARNINGRULE_H_

// Library Includes
#include <list>
#include <map>

// Includes
#include "Learning\AbstractLearningRule.hpp"

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
	// Enables teacherForcing which can speed up the learning progress
	bool teacherForcing;
	RealTimeRecurrentLearningRuleOptions()
	{
		learningRate = 0.45f;
		offlineLearning = false;
		teacherForcing = true;
	}
};

// The RealTimeRecurrentLearningRule can be used to train any sort of recurrent network
class RealTimeRecurrentLearningRule : public AbstractLearningRule
{
private:	
	// Holds all teachingInputs for all neurons in all timesteps of the current teaching lesson (needed for teacherForcing)
	std::unique_ptr<ErrorMap_t> currentTeachingInputMap;
	// Holds all output values in every timestep
	std::vector<std::map<AbstractNeuron*, float>> outputValuesInTime;
	// Holds all netInput values in every timestep
	std::vector<std::map<AbstractNeuron*, float>> netInputValuesInTime;
	// This vector should hold all delta values
	std::map<Edge*, std::map<StandardNeuron*, std::map<int, std::pair<float, bool>>>> dynamicSystemCache;
	// Returns the value of the dynamic system of an edge at a specific time point
	float getDynamicSystemValueOfEdgeAtTime(Edge* edge, StandardNeuron* neuron, int time, bool isInFirstCalculationLayer, ErrorMap_t* errormap);
	// The current network topology
	AbstractNetworkTopology* currentNetworkTopology;
	// The current time step
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
	virtual float calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork);
	bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);
	std::vector<std::map<AbstractNeuron*, float>>* getOutputValuesInTime();
	std::vector<std::map<AbstractNeuron*, float>>* getNetInputValuesInTime();
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
public:
	RealTimeRecurrentLearningRule(RealTimeRecurrentLearningRuleOptions& options_);
};

#endif

