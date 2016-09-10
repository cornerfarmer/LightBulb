#pragma once

#ifndef _LVQ1LEARNINGRULELEARNINGRULE_H_
#define _LVQ1LEARNINGRULELEARNINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "ClusterAnalysis/AbstractRBFNeuronPlacer.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetwork;
	class Teacher;

	struct LVQ1LearningRuleOptions : AbstractLearningRuleOptions
	{
		// Sets the learning Rate
		double learningRate;
		LVQ1LearningRuleOptions()
		{
			learningRate = 0.1;
		}
	};

	// The LVQ1LearningRule can only be used to train LVQNetworks
	class LVQ1LearningRule : public AbstractLearningRule
	{
	private:

	protected:
		// Returns our current options in form of a LVQ1LearningRuleOptions object
		LVQ1LearningRuleOptions* getOptions();
		// Inherited:
		void adjustWeight(Edge* edge, double deltaWeight);
		void printDebugOutput();
		bool learningHasStopped();
		void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
		AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
		double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
		void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	public:
		LVQ1LearningRule(LVQ1LearningRuleOptions &options_);
	};
}

#endif