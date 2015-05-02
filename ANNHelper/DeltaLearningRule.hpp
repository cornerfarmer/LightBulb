#pragma once

#ifndef _DELTALEARNINGRULE_H_
#define _DELTALEARNINGRULE_H_

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks or RBFNetworks
class DeltaLearningRule : public AbstractLearningRule
{
private:
protected:
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);
	AbstractActivationOrder* getNewActivationOrder();
	float calculateDeltaWeightFromEdge(Edge* edge, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
public:
	DeltaLearningRule(AbstractLearningRuleOptions &options_);

};

#endif