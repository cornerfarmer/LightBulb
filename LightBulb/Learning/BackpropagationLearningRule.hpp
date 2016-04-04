#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULE_H_
#define _BACKPROPAGATIONLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>
#include <EigenSrc/Dense>

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "Learning/ResilientLearningRateHelper.hpp"
#include <cereal/access.hpp>

// Forward declarations
class Teacher;
class Edge;
class AbstractNeuron;

struct BackpropagationLearningRuleOptions : public AbstractLearningRuleOptions
{	
		
	double flatSpotEliminationFac;
	// Sets the weight decay factor, which will be used avoid high weights
	double weightDecayFac;
	// Sets the momentum, which can improve learning speed
	double momentum;
	// Sets the learning Rate
	double learningRate;	
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
	template <class Archive>
	friend void serialize(Archive& archive, BackpropagationLearningRule& learningRule);
	friend struct cereal::LoadAndConstruct<BackpropagationLearningRule>;
private:	
	// Contains all previous deltaWeights (used by the momentum term)
	std::vector<Eigen::MatrixXd> previousDeltaWeights;
	// This vector should hold all delta values
	std::vector<Eigen::VectorXd> deltaVectorOutputLayer;
	// Check and adjust all given options
	void initialize();
protected:
	// The resilient learning rate helper is used when resilientLearningRate is activated
	std::unique_ptr<ResilientLearningRateHelper> resilientLearningRateHelper;
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeights(int layerIndex, Eigen::MatrixXd gradients);
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	BackpropagationLearningRuleOptions* getOptions();
	// Calculate the delta weight value of the given edge
	Eigen::MatrixXd calculateDeltaWeight(int layerIndex, Eigen::MatrixXd& gradients);
	// Inherited:
	std::string printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	Eigen::MatrixXd calculateDeltaWeightFromLayer(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap);
	void initializeLayerCalculation(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap);
	AbstractActivationOrder* getNewActivationOrder(AbstractNeuralNetwork &neuralNetwork);
	void initializeTry(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	BackpropagationLearningRule(BackpropagationLearningRuleOptions& options_);
	BackpropagationLearningRule(BackpropagationLearningRuleOptions* options_);
};

#endif

