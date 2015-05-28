#pragma once

#ifndef _ABSTRACTBACKPROPAGATIONLEARNINGRULE_H_
#define _ABSTRACTBACKPROPAGATIONLEARNINGRULE_H_

// Library includes
#include <map>

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class AbstractActivationOrder;
class AbstractNeuron;
class Edge;

struct AbstractBackpropagationLearningRuleOptions : AbstractLearningRuleOptions
{	
	float flatSpotEliminationFac;
	// Sets the weight decay factor, which will be used avoid high weights
	float weightDecayFac;

	AbstractBackpropagationLearningRuleOptions()
	{
		flatSpotEliminationFac = 0.1f;
		weightDecayFac = 0.02f;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class AbstractBackpropagationLearningRule : public AbstractLearningRule
{
private:	
	// This vector should hold all delta values
	std::map<AbstractNeuron*, float> deltaVectorOutputLayer;
protected:		
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	AbstractBackpropagationLearningRuleOptions* getOptions();
	// Inherited:	
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
	float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	AbstractActivationOrder* getNewActivationOrder();
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	// Initializes all required values
	AbstractBackpropagationLearningRule(AbstractBackpropagationLearningRuleOptions *options_);
};

#endif

