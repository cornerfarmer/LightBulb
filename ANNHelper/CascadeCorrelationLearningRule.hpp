#pragma once

#ifndef _CASCADECORRELATIONLEARNINGRULE_H_
#define _CASCADECORRELATIONLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "AbstractLearningRule.hpp"
#include "BackpropagationLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;
class Edge;
class AbstractNeuron;
class CascadeCorrelationNetwork;

struct CascadeCorrelationLearningRuleOptions : public AbstractLearningRuleOptions
{	

	BackpropagationLearningRuleOptions backpropagationLearningRuleOptions;
	
	unsigned int addNeuronAfterIterationInterval;

	bool addNeuronAfterLearningHasStopped;

	unsigned int candidateUnitCount;
	CascadeCorrelationLearningRuleOptions()
	{
		addNeuronAfterIterationInterval = 20000;
		addNeuronAfterLearningHasStopped = true;
		candidateUnitCount = 8;
	}
};

enum Mode
{
	OUTPUTNEURONSLEARNINGMODE,	
	CANDIDATEUNITLEARNINGMODE,
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class CascadeCorrelationLearningRule : public AbstractLearningRule
{
private:
	Mode currentMode;
	std::vector<StandardNeuron*> currentCandidateUnits;	
	std::unique_ptr<BackpropagationLearningRule> backpropagationLearningRule;
	CascadeCorrelationNetwork* currentNetworkTopology;
	Teacher* currentTeacher;
	std::map<AbstractTeachingLesson*, std::map<AbstractNeuron*, float>> neuronOutputCache;
	std::map<StandardNeuron*, std::map<AbstractTeachingLesson*, float>> candidatesNetInputCache;
	std::map<StandardNeuron*, std::map<StandardNeuron*, float>> correlations;
	std::map<AbstractTeachingLesson*, std::map<StandardNeuron*, float>> errorFactors;
protected:
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeight(Edge* edge, float gradient);
	// Returns our current options in form of a CascadeCorrelationLearningRuleOptions object
	CascadeCorrelationLearningRuleOptions* getOptions();

	float getTotalCorrelationOfUnit(StandardNeuron* candidateUnit);
	void calcAllCorrelations(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder, bool calcErrorFactor);
	// Inherited:
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);	
	virtual float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
	void initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);
public:
	CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_);
};

#endif

