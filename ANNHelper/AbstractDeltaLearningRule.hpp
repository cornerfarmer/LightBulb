#pragma once

#ifndef _ABSTRACTDELTALEARNINGRULE_H_
#define _ABSTRACTDELTALEARNINGRULE_H_

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks or RBFNetworks
class AbstractDeltaLearningRule : public AbstractLearningRule
{
protected:
	virtual void initializeDeltaLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher) {};
	// Inherited:
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);	
	AbstractActivationOrder* getNewActivationOrder();
	float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	AbstractDeltaLearningRule(AbstractLearningRuleOptions *options_);
};

#endif