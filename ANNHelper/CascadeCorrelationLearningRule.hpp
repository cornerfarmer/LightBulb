#pragma once

#ifndef _CASCADECORRELATIONLEARNINGRULE_H_
#define _CASCADECORRELATIONLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "AbstractLearningRule.hpp"
#include "BackpropagationLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;
class AbstractNeuron;
class AbstractNetworkTopology;

struct CascadeCorrelationLearningRuleOptions : public AbstractLearningRuleOptions
{	

	BackpropagationLearningRuleOptions backpropagationLearningRuleOptions;
	CascadeCorrelationLearningRuleOptions()
	{

	}
};

enum Mode
{
	OUTPUTNEURONSLEARNINGMODE,
	MEANCALCULATIONMODE,
	CANDIDATEUNITLEARNINGMODE,
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class CascadeCorrelationLearningRule : public AbstractLearningRule
{
private:
	Mode currentMode;
	StandardNeuron* currentCandidateUnit;	
	std::unique_ptr<BackpropagationLearningRule> backpropagationLearningRule;
	AbstractNetworkTopology* currentNetworkTopology;
	std::map<StandardNeuron*, float> correlationSigns;
	std::map<StandardNeuron*, float> meanOutputs;
	std::map<StandardNeuron*, float> meanErrorValues;
protected:
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Returns our current options in form of a CascadeCorrelationLearningRuleOptions object
	CascadeCorrelationLearningRuleOptions* getOptions();
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);	
	virtual float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
	void initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_);
};

#endif

