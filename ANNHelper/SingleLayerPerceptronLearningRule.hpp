#pragma once

#ifndef _SINGLELAYERPERCEPTRONLEARNINGRULE_H_
#define _SINGLELAYERPERCEPTRONLEARNINGRULE_H_

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

// The PerceptronLearningRule can only be used to train binary SingleLayerPerceptronNetworks
class SingleLayerPerceptronLearningRule : public AbstractLearningRule
{
private:
// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);
	AbstractActivationOrder* getNewActivationOrder();
	float calculateDeltaWeightFromEdge(Edge* edge, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	SingleLayerPerceptronLearningRule(AbstractLearningRuleOptions &options_);
};

#endif