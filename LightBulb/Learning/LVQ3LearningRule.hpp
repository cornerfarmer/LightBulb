#pragma once

#ifndef _LVQ3LEARNINGRULELEARNINGRULE_H_
#define _LVQ3LEARNINGRULELEARNINGRULE_H_

// Includes
#include "Learning\AbstractLearningRule.hpp"
#include "ClusterAnalysis\AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct LVQ3LearningRuleOptions : AbstractLearningRuleOptions
{	
	// Sets the learning Rate
	double learningRate;
	// The relativeWindow describes the area where neurons will be moved
	double relativeWindow;
	// The learningRate if the two winner neurons and the teachingInput are in the same class
	double sameClassesLearningRateFactor;
	LVQ3LearningRuleOptions()
	{
		learningRate = 0.1;
		relativeWindow = 0.3;
		sameClassesLearningRateFactor = 0.3;
	}
};

// The LVQ3LearningRule can only be used to train LVQNetworks
class LVQ3LearningRule : public AbstractLearningRule
{
private:
	StandardNeuron* firstWinnerNeuron;
	StandardNeuron* secondWinnerNeuron;
	bool changeWeights;
	bool sameClasses;
protected:
	// Returns our current options in form of a LVQ3LearningRuleOptions object
	LVQ3LearningRuleOptions* getOptions();	
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
	LVQ3LearningRule(LVQ3LearningRuleOptions &options_);
};

#endif