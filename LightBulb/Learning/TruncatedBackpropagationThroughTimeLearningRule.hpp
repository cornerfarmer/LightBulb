#pragma once

#ifndef _TRUNCATEDBACKPROPAGATIONTHROUGHTIMELEARNINGRULE_H_
#define _TRUNCATEDBACKPROPAGATIONTHROUGHTIMELEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "Learning\BackpropagationLearningRule.hpp"
#include "Learning\BackpropagationThroughTimeLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class AbstractNeuron;
class Edge;

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class TruncatedBackpropagationThroughTimeLearningRule : public BackpropagationLearningRule
{
	friend class CascadeCorrelationLearningRule;
private:	
	// Holds all output values in every timestep
	std::vector<std::map<AbstractNeuron*, double>> outputValuesInTime;
	// Holds all netInput values in every timestep
	std::vector<std::map<AbstractNeuron*, double>> netInputValuesInTime;
	// Contains for every edge the information, if its neurons are in the same time step
	std::unique_ptr<std::map<Edge*, bool>> sameTimestepEdges;
	// This vector should hold all delta values in all timesteps (The boolean value holds the information, if the deltavalue is valid)
	std::map<AbstractNeuron*, std::vector<std::pair<double, bool>>> deltaVectorOutputLayer;
	// Returns and calculated (if needed) the delta value of a neuron in the given timestep
	double getDeltaVectorOfNeuronInTime(StandardNeuron* neuron, int time, ErrorMap_t* errormap);
protected:
	// Returns our current options in form of a BackpropagationThroughTimeLearningRuleOptions object
	BackpropagationThroughTimeLearningRuleOptions* getOptions();
	// Inherited:
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);	
	double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	std::vector<std::map<AbstractNeuron*, double>>* getOutputValuesInTime();
	void initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap);
	std::vector<std::map<AbstractNeuron*, double>>* getNetInputValuesInTime();
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);
public:
	TruncatedBackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_);
};

#endif

