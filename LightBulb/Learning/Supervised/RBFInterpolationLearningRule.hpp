#pragma once

#ifndef _RBFINTERPOLATIONLEARNINGRULE_H_
#define _RBFINTERPOLATIONLEARNINGRULE_H_

// Library Includes
#include "EigenSrc/Dense"
#include "EigenSrc/Jacobi"
#include <memory>

// Includes
#include "ClusterAnalysis/AbstractRBFNeuronPlacer.hpp"
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct RBFInterpolationLearningRuleOptions : AbstractSupervisedLearningRuleOptions
{	
	// The neuronPlacer helps to replace all RBFNeurons before starting to learn
	AbstractRBFNeuronPlacer* neuronPlacer;
	RBFInterpolationLearningRuleOptions()
	{
		
	}
	~RBFInterpolationLearningRuleOptions()
	{
		delete(neuronPlacer);
	}
	RBFInterpolationLearningRuleOptions(const RBFInterpolationLearningRuleOptions &obj)
	{
		*this = obj;
		neuronPlacer = obj.neuronPlacer->getCopy();
	}
};

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks
class RBFInterpolationLearningRule : public AbstractSupervisedLearningRule
{
private:
	// A matrix which will contain all outputValues from neurons in the second layer in every teachingLesson
	std::unique_ptr<Eigen::MatrixXd> m;
	// Inversion of m
	std::unique_ptr<Eigen::MatrixXd> mInverse;
	// A matrx which will contain all teachingInput values from all output neurons
	std::unique_ptr<Eigen::MatrixXd> t;
	// A vector which will contain all calculated weights
	std::unique_ptr<Eigen::MatrixXd> w;
protected:
	// Returns our current options in form of a RBFInterpolatioLearningRuleOptions object
	RBFInterpolationLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeights(int layerIndex, Eigen::MatrixXd gradients);
	bool learningHasStopped();
	void initializeStartLearningAlgoritm();
	AbstractActivationOrder* getNewActivationOrder();
	std::vector<Eigen::MatrixXd> calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap);
	void initializeLayerCalculation(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap);
	void initializeTry();
public:
	RBFInterpolationLearningRule(RBFInterpolationLearningRuleOptions &options_);
	static std::string getName();
};

#include "IO/RBFInterpolationLearningRuleIO.hpp"

#endif
