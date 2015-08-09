#pragma once

#ifndef _SOMLEARNINGRULELEARNINGRULE_H_
#define _SOMLEARNINGRULELEARNINGRULE_H_

// Includes
#include "Learning\AbstractLearningRule.hpp"
#include "ClusterAnalysis\AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class AbstractNeighborhoodFunction;
class AbstractShrinkFunction;

struct SOMLearningRuleOptions : AbstractLearningRuleOptions
{	
	// Sets the learning Rate
	double learningRate;

	AbstractNeighborhoodFunction* neighborhoodFunction;

	AbstractShrinkFunction* distanceShrinkFunction;

	SOMLearningRuleOptions()
	{
		learningRate = 0.1;
		neighborhoodFunction = NULL;
		distanceShrinkFunction = NULL;
	}
	~SOMLearningRuleOptions();
	SOMLearningRuleOptions::SOMLearningRuleOptions(const SOMLearningRuleOptions &obj);
};

// The LVQ1LearningRule can only be used to train LVQNetworks
class SOMLearningRule : public AbstractLearningRule
{
private:
	int currentTimestep;
	StandardNeuron* currentActivatedNeuron;
protected:
	// Returns our current options in form of a SOMLearningRuleOptions object
	SOMLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, double deltaWeight);
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
public:
	SOMLearningRule(SOMLearningRuleOptions &options_);
};

#endif