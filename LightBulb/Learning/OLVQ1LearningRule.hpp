#pragma once

#ifndef _OLVQ1LEARNINGRULELEARNINGRULE_H_
#define _OLVQ1LEARNINGRULELEARNINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "ClusterAnalysis/AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct OLVQ1LearningRuleOptions : AbstractLearningRuleOptions
{	

	double learningRateStart;
	OLVQ1LearningRuleOptions()
	{
		learningRateStart = 0.3;
	}
};

// The LVQ1OLVQ1LearningRuleLearningRule can only be used to train LVQNetworks
class OLVQ1LearningRule : public AbstractLearningRule
{
private:
	std::map<StandardNeuron*, double> learningRates;
protected:
	// Returns our current options in form of a LVQ1LearningRuleOptions object
	OLVQ1LearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, double deltaWeight);
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap);
public:
	OLVQ1LearningRule(OLVQ1LearningRuleOptions &options_);
};

#endif