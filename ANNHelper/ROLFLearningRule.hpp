#pragma once

#ifndef _ROLFLEARNINGRULE_H_
#define _ROLFLEARNINGRULE_H_

// Includes
#include "AbstractLearningRule.hpp"
#include "AbstractClustering.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct ROLFLearningRuleOptions : public AbstractLearningRuleOptions
{
	float centerLearningRate;
	float widthLearningRate;
	float widthMultiplier;
	ROLFLearningRuleOptions()
	{
		widthMultiplier = 2;
		centerLearningRate = 0.05;
		widthLearningRate = 0.05;
		totalErrorGoal = 0;
		maxIterationsPerTry = 10000;
		maxTries = 1;
	}
};

// The PerceptronLearningRule can only be used to train binary SingleLayerPerceptronNetworks
class ROLFLearningRule : public AbstractLearningRule, AbstractClustering
{
private:
	Teacher* currentTeacher;
	NeuralNetwork* currentNeuralNetwork;
	ROLFLearningRuleOptions* getOptions();
	bool lerningHasStopped;
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);
	AbstractActivationOrder* getNewActivationOrder();
	float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
public:
	ROLFLearningRule(ROLFLearningRuleOptions &options_);
};

#endif