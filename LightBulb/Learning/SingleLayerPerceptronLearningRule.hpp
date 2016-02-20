#pragma once

#ifndef _SINGLELAYERPERCEPTRONLEARNINGRULE_H_
#define _SINGLELAYERPERCEPTRONLEARNINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The PerceptronLearningRule can only be used to train binary SingleLayerPerceptronNetworks
class SingleLayerPerceptronLearningRule : public AbstractLearningRule
{
private:
	// Inherited:
	void adjustWeight(Edge* edge, double deltaWeight);
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	double calculateDeltaWeightFromEdge(Edge* edge, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errorvector);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	SingleLayerPerceptronLearningRule(AbstractLearningRuleOptions &options_);
};

#endif