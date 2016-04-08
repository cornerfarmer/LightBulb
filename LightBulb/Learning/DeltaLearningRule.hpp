#pragma once

#ifndef _DELTALEARNINGRULE_H_
#define _DELTALEARNINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "ClusterAnalysis/AbstractRBFNeuronPlacer.hpp"
#include "Learning/ResilientLearningRateHelper.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct DeltaLearningRuleOptions : AbstractLearningRuleOptions
{	
	// The neuronPlacer helps to replace all RBFNeurons before starting to learn (Only needed when training RBFNetworks)
	AbstractRBFNeuronPlacer* neuronPlacer;
	// Sets the learning Rate
	double learningRate;	
	// Selects if a resilient learning rate should be used (This option can not be used at the same time with the momentum term)
	bool resilientLearningRate;
	// Holds all options which are needed for the resilient learning rate
	ResilientLearningRateHelperOptions resilientLearningRateOptions;
	DeltaLearningRuleOptions()
	{
		neuronPlacer = NULL;
	}
	~DeltaLearningRuleOptions()
	{
		delete(neuronPlacer);
	}
	DeltaLearningRuleOptions(const DeltaLearningRuleOptions &obj)
	{
		*this = obj;
		if (neuronPlacer)
			neuronPlacer = obj.neuronPlacer->getCopy();
		else
			neuronPlacer = 0;
	}
};

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks or RBFNetworks
class DeltaLearningRule : public AbstractLearningRule
{
private:
	DeltaLearningRuleOptions* getOptions();
	std::unique_ptr<ResilientLearningRateHelper> resilientLearningRateHelper;
	// Inherited:
	void initializeLearningAlgoritm(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(AbstractNeuralNetwork &neuralNetwork);
	Eigen::MatrixXd calculateDeltaWeightFromLayer(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap);
	void adjustWeights(int layerIndex, Eigen::MatrixXd gradients);
	void initializeTry(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher);
	bool learningHasStopped();	
	std::string printDebugOutput();
public:
	DeltaLearningRule(DeltaLearningRuleOptions &options_);
	std::string getName();
};

#endif