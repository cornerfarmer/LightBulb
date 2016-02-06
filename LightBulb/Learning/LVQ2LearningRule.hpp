#pragma once

#ifndef _LVQ2LEARNINGRULELEARNINGRULE_H_
#define _LVQ2LEARNINGRULELEARNINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "ClusterAnalysis/AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct LVQ2LearningRuleOptions : AbstractLearningRuleOptions
{	
	// Sets the learning Rate
	double learningRate;
	// The relativeWindow describes the area where neurons will be moved
	double relativeWindow;
	LVQ2LearningRuleOptions()
	{
		learningRate = 0.1;
		relativeWindow = 0.4;
	}
};

// The LVQ2LearningRule can only be used to train LVQNetworks
class LVQ2LearningRule : public AbstractLearningRule
{
private:
	StandardNeuron* firstWinnerNeuron;
	StandardNeuron* secondWinnerNeuron;
	bool changeWeights;
protected:
	// Returns our current options in form of a LVQ1LearningRuleOptions object
	LVQ2LearningRuleOptions* getOptions();	
	// Inherited:
	void adjustWeight(Edge* edge, double deltaWeight);
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
public:
	LVQ2LearningRule(LVQ2LearningRuleOptions &options_);
};

#endif