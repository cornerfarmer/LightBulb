#pragma once

#ifndef _ABSTRACTDELTALEARNINGRULE_H_
#define _ABSTRACTDELTALEARNINGRULE_H_

// Includes
#include "AbstractLearningRule.hpp"
#include "AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct AbstractDeltaLearningRuleOptions : AbstractLearningRuleOptions
{	
	// The neuronPlacer helps to replace all RBFNeurons before starting to learn (Only needed when training RBFNetworks)
	AbstractRBFNeuronPlacer* neuronPlacer;
	AbstractDeltaLearningRuleOptions()
	{
		neuronPlacer = NULL;
	}
	~AbstractDeltaLearningRuleOptions()
	{
		delete(neuronPlacer);
	}
	AbstractDeltaLearningRuleOptions(const AbstractDeltaLearningRuleOptions &obj)
	{
		*this = obj;
		if (neuronPlacer)
			neuronPlacer = obj.neuronPlacer->getCopy();
		else
			neuronPlacer = 0;
	}
};

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks or RBFNetworks
class AbstractDeltaLearningRule : public AbstractLearningRule
{
protected:
	AbstractDeltaLearningRuleOptions* getOptions();
	virtual void initializeDeltaLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher) {};
	// Inherited:
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);	
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	AbstractDeltaLearningRule(AbstractDeltaLearningRuleOptions *options_);
};

#endif