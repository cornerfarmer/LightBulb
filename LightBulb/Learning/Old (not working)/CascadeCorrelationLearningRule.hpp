#pragma once

#ifndef _CASCADECORRELATIONLEARNINGRULE_H_
#define _CASCADECORRELATIONLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "Learning/BackpropagationLearningRule.hpp"
#include "Learning/TruncatedBackpropagationThroughTimeLearningRule.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetwork;
	class Teacher;
	class Edge;
	class AbstractNeuron;
	class CascadeCorrelationNetwork;

	struct CascadeCorrelationLearningRuleOptions : public AbstractLearningRuleOptions
	{
		// The backpropagation learning rule options for the training of the output neurons
		BackpropagationThroughTimeLearningRuleOptions outputNeuronsLearningRuleOptions;
		// The backpropagation learning rule options for the training of the candidate units
		BackpropagationLearningRuleOptions candidateUnitsLearningRuleOptions;
		// Add a new neuron after every n-th iteration (0 disables this feature)
		unsigned int addNeuronAfterIterationInterval;
		// Add a new neuron after the learning process has stopped
		bool addNeuronAfterLearningHasStopped;
		// The size of the candidate unit group which will be trained at the same time
		unsigned int candidateUnitCount;
		// Create a recurrent network (Adds a self referencing edge to every cascade unit)
		bool recurrent;
		CascadeCorrelationLearningRuleOptions()
		{
			addNeuronAfterIterationInterval = 20000;
			addNeuronAfterLearningHasStopped = true;
			candidateUnitCount = 8;
			recurrent = false;
		}
	};

	// The different modes the learning rule can be into
	enum Mode
	{
		OUTPUTNEURONSLEARNINGMODE,
		CANDIDATEUNITLEARNINGMODE,
	};

	// The CascadeCorrelationLearningRule can be used to train CascadeCorrelationNetworks
	class CascadeCorrelationLearningRule : public AbstractLearningRule
	{
	private:
		// Holds the current mode
		Mode currentMode;
		// Holds all current trained candidate units
		std::vector<StandardNeuron*> currentCandidateUnits;
		// Holds the backpropagation learning rule for training of the candidate units
		std::unique_ptr<BackpropagationLearningRule> candidateUnitsBackpropagationLearningRule;
		// Holds the backpropagation learning rule for training of the output neurons
		std::unique_ptr<TruncatedBackpropagationThroughTimeLearningRule> outputNeuronsBackpropagationLearningRule;
		// The current network toplogy
		CascadeCorrelationNetwork* currentNetworkTopology;
		// The current teacher
		Teacher* currentTeacher;

		std::map<AbstractTeachingLesson*, std::map<Edge*, std::map<int, std::pair<double, bool>>>> outputGradientCache;
		// The cache of every output of every neuron in every timestep in every teaching lesson
		std::map<AbstractTeachingLesson*, std::vector<std::map<AbstractNeuron*, double>>> neuronOutputCache;
		// The cache of every net input of every candidate unit int every timestep in every teaching lesson
		std::map<StandardNeuron*, std::map<AbstractTeachingLesson*, std::vector<double>>> candidatesNetInputCache;
		// Holds all current correlation values of all output neurons corresponding to all candidate units
		std::map<StandardNeuron*, std::map<StandardNeuron*, double>> correlations;
		// Holds all current error factors of all output neurons in all teaching lessons
		std::map<AbstractTeachingLesson*, std::map<int, std::map<StandardNeuron*, double>>> errorFactors;
		// Computes the output gradient of an edge in a given time and lesson
		double getOutputGradient(Edge* edge, int time, AbstractTeachingLesson* lesson);
		double getOutputGradientCached(Edge* edge, int time, AbstractTeachingLesson* lesson);
		double calcOutputGradient(Edge* edge, int time, AbstractTeachingLesson* lesson);
	protected:
		// Adjusts the weights of an edge dependent on its gradient
		void adjustWeight(Edge* edge, double gradient);
		// Returns our current options in form of a CascadeCorrelationLearningRuleOptions object
		CascadeCorrelationLearningRuleOptions* getOptions();
		// Computes the total correlation of a candidate unit
		double getTotalCorrelationOfUnit(StandardNeuron* candidateUnit);
		// Recalculates all correaltion of all candidate units
		void calcAllCorrelations(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder, bool calcErrorFactor);
		// Inherited:
		void printDebugOutput();
		bool learningHasStopped();
		void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
		virtual double calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
		void initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap);
		AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
		void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
		void initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson);
		void initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
		bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);
		std::vector<std::map<AbstractNeuron*, double>>* getOutputValuesInTime();
		std::vector<std::map<AbstractNeuron*, double>>* getNetInputValuesInTime();
	public:
		CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_);
	};
}

#endif
