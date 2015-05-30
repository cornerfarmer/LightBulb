#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULE_H_
#define _BACKPROPAGATIONLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "AbstractLearningRule.hpp"
#include "ResilientLearningRateHelper.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;
class AbstractNeuron;

struct BackpropagationLearningRuleOptions : public AbstractLearningRuleOptions
{	
		
	float flatSpotEliminationFac;
	// Sets the weight decay factor, which will be used avoid high weights
	float weightDecayFac;
	// Sets the momentum, which can improve learning speed
	float momentum;
	// Sets the learning Rate
	float learningRate;	

	bool resilientLearningRate;

	ResilientLearningRateHelperOptions resilientLearningRateOptions;
	BackpropagationLearningRuleOptions()
	{
		flatSpotEliminationFac = 0.1f;
		weightDecayFac = 0.02f;
		momentum = 0.7f;
		learningRate = 0.45f;
		offlineLearning = false;
		resilientLearningRate = false;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class BackpropagationLearningRule : public AbstractLearningRule
{
private:	
	// This vector should hold all delta values
	std::map<AbstractNeuron*, float> deltaVectorOutputLayer;
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Contains all previous deltaWeights (used by the momentum term)
	std::unique_ptr<std::vector<float>> previousDeltaWeights;	
	std::unique_ptr<ResilientLearningRateHelper> resilientLearningRateHelper;
	void initialize();
protected:
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	BackpropagationLearningRuleOptions* getOptions();
	float calculateDeltaWeight(Edge* edge, float gradient);
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
	float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	AbstractActivationOrder* getNewActivationOrder();
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	BackpropagationLearningRule(BackpropagationLearningRuleOptions options_);
	BackpropagationLearningRule(BackpropagationLearningRuleOptions* options_);
};

#endif

