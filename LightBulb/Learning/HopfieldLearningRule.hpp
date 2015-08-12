#pragma once

#ifndef _HOPFIELDLEARNINGRULE_H_
#define _HOPFIELDLEARNINGRULE_H_

// Includes
#include "Learning\AbstractLearningRule.hpp"
#include "ClusterAnalysis\AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class AbstractTeachingLesson;

struct HopfieldLearningRuleOptions : AbstractLearningRuleOptions
{	
	bool trainHeteroassociation;

	HopfieldLearningRuleOptions()
	{
		trainHeteroassociation = false;
	}
};

// The CounterpropagationLearningRule can only be used to train CounterpropagationNetworks
class HopfieldLearningRule : public AbstractLearningRule
{
private:
protected:
	// Returns our current options in form of a CounterpropagationLearningRuleOptions object
	HopfieldLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, double deltaWeight);
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);
public:
	HopfieldLearningRule(HopfieldLearningRuleOptions &options_);
};

#endif