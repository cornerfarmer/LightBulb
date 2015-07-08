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
	// Selects if a resilient learning rate should be used (This option can not be used at the same time with the momentum term)
	bool resilientLearningRate;
	// Holds all options which are needed for the resilient learning rate
	ResilientLearningRateHelperOptions resilientLearningRateOptions;
	BackpropagationLearningRuleOptions()
	{
		flatSpotEliminationFac = 0.1f;
		weightDecayFac = 0;
		momentum = 0.7f;
		learningRate = 0.45f;
		offlineLearning = false;
		resilientLearningRate = false;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class BackpropagationLearningRule : public AbstractLearningRule
{
	friend class CascadeCorrelationLearningRule;
private:	
	// Contains all previous deltaWeights (used by the momentum term)
	std::map<Edge*, float> previousDeltaWeights;	
	// This vector should hold all delta values
	std::map<AbstractNeuron*, float> deltaVectorOutputLayer;
	// Check and adjust all given options
	void initialize();
protected:
	// The resilient learning rate helper is used when resilientLearningRate is activated
	std::unique_ptr<ResilientLearningRateHelper> resilientLearningRateHelper;
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	BackpropagationLearningRuleOptions* getOptions();
	// Calculate the delta weight value of the given edge
	float calculateDeltaWeight(Edge* edge, float gradient);
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);	
	virtual float calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	BackpropagationLearningRule(BackpropagationLearningRuleOptions& options_);
	BackpropagationLearningRule(BackpropagationLearningRuleOptions* options_);
};

#endif

