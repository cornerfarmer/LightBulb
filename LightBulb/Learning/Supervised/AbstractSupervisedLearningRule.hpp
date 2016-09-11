#pragma once

#ifndef _ABSTRACTSUPERVISEDLEARNINGRULE_H_
#define _ABSTRACTSUPERVISEDLEARNINGRULE_H_

// Library Includes´
#include <EigenSrc/Dense>
#include <vector>
#include <map>
#include <memory>
#include <Logging/AbstractLogger.hpp>

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "Learning/AbstractLearningRule.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	class Teacher;
	class AbstractTeachingLesson;
	class AbstractNetworkTopology;

	typedef std::vector<Eigen::VectorXd> ErrorMap_t;

#define DATA_SET_TRAINING_ERROR "Training error"


	struct AbstractSupervisedLearningRuleOptions : public AbstractLearningRuleOptions
	{

		// Sets the highest total error value, when the algorithm should finish successful
		double totalErrorGoal;
		// Sets the lower limit of the random generated weights
		double minRandomWeightValue;
		// Sets the higher limit of the random generated weights
		double maxRandomWeightValue;
		// Sets the minium iterations per try
		unsigned int minIterationsPerTry;
		// Sets the maximum total error value (If a try has after its miniums iterations a greater total error value than the maxTotalErrorValue, skip that try)
		double maxTotalErrorValue;
		// Enable offline learning
		bool offlineLearning;
		// Can be used to prevent the learning rule to change the weights of the network before the learning begins
		bool changeWeightsBeforeLearning;

		AbstractNeuralNetwork* neuralNetwork;

		Teacher* teacher;

		bool clipError;
		AbstractSupervisedLearningRuleOptions()
		{
			totalErrorGoal = 0.01;
			minRandomWeightValue = -0.5f;
			maxRandomWeightValue = 0.5f;
			minIterationsPerTry = 1000;
			maxTotalErrorValue = 2;
			offlineLearning = false;
			changeWeightsBeforeLearning = true;
			neuralNetwork = NULL;
			teacher = NULL;
			clipError = false;
		}
		virtual ~AbstractSupervisedLearningRuleOptions() {}
	};

	// A LearningRule is used to improve a AbstractNeuralNetwork
	class AbstractSupervisedLearningRule : public AbstractLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractSupervisedLearningRule& learningRule);
	private:
		void validateOptions();
	protected:
		// Holds the current total error
		double totalError;

		std::unique_ptr<AbstractActivationOrder> currentActivationOrder;
		// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
		AbstractSupervisedLearningRuleOptions* getOptions();
		bool doIteration() override;
		void initializeStartLearningAlgoritm() override;
		void initializeResumeLearningAlgoritm() override;
		void initializeLearningAlgoritm() override;
		bool hasLearningSucceeded() override;
		void rateLearning() override;
		virtual void clearGradient() {};
		// This method should calculate the deltaWeight for the actual edge
		virtual void calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap) = 0;
		// This method should adjust the weight of the current edge
		virtual void adjustWeights(int layerIndex) = 0;
		// Calculate if it is sensible to continue learning
		virtual bool learningHasStopped() = 0;
		// Prints a current summary of the status of the learning process
		virtual std::string printDebugOutput() { return ""; };
		// This method should do something like randomizing all weight
		void initializeTry() override = 0;
		// This method can be used to do some work before every iteration
		virtual void initializeIteration() { };
		// This method can be used to do some work before every teaching lesson
		virtual void initializeTeachingLesson(AbstractTeachingLesson &teachingLesson) { };
		// This method could be used to do some work after all weights has been adjusted
		virtual void doCalculationAfterAllWeightAdjustments() { };
		// This method could be used to do some work befora all weights are adjusted
		virtual void initializeAllWeightAdjustments() { };
		// This method could be used to do some prework on the AbstractNeuralNetwork
		virtual AbstractNeuralNetwork* initializeNeuralNetwork(AbstractNeuralNetwork &neuralNetwork) { return &neuralNetwork; };
		// This method could be used to do some prework on the teacher
		virtual Teacher* initializeTeacher(Teacher &teacher) { return &teacher; };
		// This method could be used to do something after the learning process
		void doCalculationAfterLearningProcess() override;
		// This method should determine the start time and time step count of the next calculation
		virtual bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);

		AbstractNetworkTopology* getCurrentNetworkTopology();

		AbstractLearningResult* getLearningResult() override;
	public:
		AbstractSupervisedLearningRule(AbstractSupervisedLearningRuleOptions& options_);
		AbstractSupervisedLearningRule(AbstractSupervisedLearningRuleOptions* options_);

		std::vector<std::string> getDataSetLabels() override;
	};
}

#include "IO/AbstractSupervisedLearningRuleIO.hpp"

#endif


