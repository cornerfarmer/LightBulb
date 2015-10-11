#pragma once

#ifndef _COUNTERPROPAGATIONLEARNINGRULE_H_
#define _COUNTERPROPAGATIONLEARNINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "ClusterAnalysis/AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct CounterpropagationLearningRuleOptions : AbstractLearningRuleOptions
{	
	// Sets the learning Rate
	double firstLayerLearningRate;

	double secondLayerLearningRate;

	int iterationsToChangeMode;

	CounterpropagationLearningRuleOptions()
	{
		firstLayerLearningRate = 0.7;
		secondLayerLearningRate = 0.1;
		iterationsToChangeMode = 1000;
	}
};

// The CounterpropagationLearningRule can only be used to train CounterpropagationNetworks
class CounterpropagationLearningRule : public AbstractLearningRule
{
private:
	int mode;
protected:
	// Returns our current options in form of a CounterpropagationLearningRuleOptions object
	CounterpropagationLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, double deltaWeight);
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
public:
	CounterpropagationLearningRule(CounterpropagationLearningRuleOptions &options_);
};

#endif