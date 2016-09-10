#pragma once

#ifndef _BACKPROPAGATIONTHROUGHTIMELEARNINGRULE_H_
#define _BACKPROPAGATIONTHROUGHTIMELEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "Learning/BackpropagationLearningRule.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetwork;
	class Teacher;
	class Edge;

	struct BackpropagationThroughTimeLearningRuleOptions : BackpropagationLearningRuleOptions
	{
		// Sets the number of time step the algorithm should simulate (All teachingLessons should have exactly one pattern for every time step)
		unsigned int maxTimeSteps;
		BackpropagationThroughTimeLearningRuleOptions()
		{
			maxTimeSteps = 1;
		}
	};

	// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
	class BackpropagationThroughTimeLearningRule : public BackpropagationLearningRule
	{
	private:
		// Adjusts the weights of an edge dependent on its gradient
		void adjustWeight(Edge* edge, double gradient);
		// This vector should hold all delta weight sums for every edge in the original network, which is the sum of all corresponding weights in the unfolded network
		std::vector<double> deltaWeightSums;
		// This variable contains the original network which is not unfolded
		NeuralNetwork* originalNeuralNetwork;
	protected:
		// Returns our current options in form of a BackpropagationThroughTimeLearningRuleOptions object
		BackpropagationThroughTimeLearningRuleOptions* getOptions();
		// Inherited:
		void doCalculationAfterAllWeightAdjustments(NeuralNetwork &neuralNetwork);
		void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
		NeuralNetwork* initializeNeuralNetwork(NeuralNetwork &neuralNetwork);
		void doCalculationAfterLearningProcess(NeuralNetwork &neuralNetwork, Teacher &teacher);
		void initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork);
		Teacher* initializeTeacher(Teacher &teacher);
		void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
	public:
		BackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_);
	};
}

#endif

