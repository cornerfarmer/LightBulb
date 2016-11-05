#pragma once

#ifndef _ABSTRACTSUPERVISEDLEARNINGRULE_H_
#define _ABSTRACTSUPERVISEDLEARNINGRULE_H_

// Library Includes´
#include <vector>
#include <memory>

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

#define DATA_SET_TRAINING_ERROR "Training error"

	/**
	* \brief All general options which are the same for all supervised learning rules.
	*/
	struct AbstractSupervisedLearningRuleOptions : public AbstractLearningRuleOptions
	{
		/**
		 * \brief Sets the total error value, when the algorithm should finish successful.
		 * \details Default value: 0.01 
		 */
		double totalErrorGoal;
		/**
		 * \brief Sets the lower limit of the random generated weights
		 * \details Default value: -0.5
		 */
		double minRandomWeightValue;
		/**
		* \brief Sets the upper limit of the random generated weights
		* \details Default value: 0.5
		*/
		double maxRandomWeightValue;
		/**
		 * \brief Sets the minium iterations per try
		 * \details The number of iterations which will at least be executed, even if the error value is higher than maxTotalErrorValue. \n
		 * Default value: 1000
		 */
		unsigned int minIterationsPerTry;
		/**
		 * \brief Sets the maximum total error value.
		 * \details If a try has - after its miniums iterations - a greater total error value than the maxTotalErrorValue, the try will be skipped. \n
		 * Default value: 2
		 */
		double maxTotalErrorValue;
		/**
		 * \brief Enables offline learning
		 * \details When offline learning is enabled, all training lessons will be evaluated before the weights are updated. \n
		 * Default value: false
		 */
		bool offlineLearning;
		/**
		 * \brief Can be used to prevent the learning rule to change the weights of the network before the learning begins.
		 * Default value: true
		 */
		bool changeWeightsBeforeLearning;
		/**
		 * \brief The neural network which should be trained.
		 */
		AbstractNeuralNetwork* neuralNetwork;
		/**
		 * \brief The teacher which contains the relevant training lessons.
		 */
		Teacher* teacher;
		/**
		 * \brief Sets if the error values (between network output and training input) should be clipped between -1 and +1
		 * \details This could prevent gradients of getting to big. \n
		 * Default value: false
		 */
		bool clipError;
		/**
		* \brief Creates the options and fills them with default options.
		*/
		AbstractSupervisedLearningRuleOptions()
		{
			totalErrorGoal = 0.01;
			minRandomWeightValue = -0.5f;
			maxRandomWeightValue = 0.5f;
			minIterationsPerTry = 1000;
			maxTotalErrorValue = 2;
			offlineLearning = false;
			changeWeightsBeforeLearning = true;
			neuralNetwork = nullptr;
			teacher = nullptr;
			clipError = false;
		}
		virtual ~AbstractSupervisedLearningRuleOptions() {}
	};

	/**
	 * \brief A supervised learning rule uses teaching lessons to train one neural network.
	 */
	class AbstractSupervisedLearningRule : public AbstractLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractSupervisedLearningRule& learningRule);
	private:
		/**
		 * \brief Validates the given options object.
		 */
		void validateOptions();
	protected:
		/**
		 * \brief Holds the current total error
		 */
		double totalError;
		/**
		 * \brief Holds the current activation order which should be used for the neural network.
		 */
		std::unique_ptr<AbstractActivationOrder> currentActivationOrder;
		/**
		 * \brief Returns our current options in form of a AbstractSupervisedLearningRuleOptions object.
		 * \return The AbstractSupervisedLearningRuleOptions
		 */
		const AbstractSupervisedLearningRuleOptions& getOptions() const;
		/**
		 * \brief This method can be used to reset any variable which holds the current gradient sum.
		 */
		virtual void clearGradient() {};
		/**
		 * \brief This method should calculate the deltaWeight for the current lesson
		 * \param lesson The current teaching lesson object.
		 * \param lessonIndex The current teaching lesson index.
		 * \param errorVector The errorVector which represents how well the neural network has done on the current teaching lesson.
		 */
		virtual void calculateDeltaWeight(const AbstractTeachingLesson& lesson, int lessonIndex, const Eigen::VectorXd& errorVector) = 0;
		/**
		 * \brief This method should adjust the weight for the current layer.
		 * \param layerIndex The index of the layer to change.
		 */
		virtual void adjustWeights(int layerIndex) = 0;
		/**
		 * \brief Calculate if it is sensible to continue learning.
		 * \return True, if learning should be stopped.
		 */
		virtual bool learningHasStopped() = 0;
		/**
		 * \brief Prints a current summary of the status of the learning process.
		 * \return The string to output.
		 */
		virtual std::string printDebugOutput() { return ""; };
		/**
		 * \brief This method can be used to do some work before every iteration.
		 */
		virtual void initializeIteration() { };
		/**
		 * \brief This method can be used to do some work before every teaching lesson.
		 * \param teachingLesson The next teaching lesson.
		 */
		virtual void initializeTeachingLesson(const AbstractTeachingLesson &teachingLesson) { };
		/**
		 * \brief This method could be used to do some work after all weights has been adjusted.
		 */
		virtual void doCalculationAfterAllWeightAdjustments() { };
		/**
		 * \brief This method could be used to do some work befora all weights are adjusted.
		 */
		virtual void initializeAllWeightAdjustments() { };
		/**
		 * \brief This method could be used to do some prework on the AbstractNeuralNetwork.
		 * \param neuralNetwork The original neural network.
		 */
		virtual void initializeNeuralNetwork(AbstractNeuralNetwork &neuralNetwork) { };
		/**
		 * \brief This method could be used to do some prework on the teacher.
		 * \param teacher The original teacher.
		 */
		virtual void initializeTeacher(Teacher &teacher) { };
		/**
		 * \brief This method should determine the start time and time step count of the next error calculation.
		 * \param nextStartTime The time step where to start.
		 * \param nextTimeStepCount The amount of steps to calculate (Should be filled).
		 * \param teachingLesson The teaching lesson.
		 * \return If false, the teaching lesson will be skipped.
		 */
		virtual bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, const AbstractTeachingLesson& teachingLesson);
		/**
		 * \brief Returns the current network topology
		 * \return The current network topology
		 */
		AbstractNetworkTopology& getCurrentNetworkTopology();
		// Inherited:
		bool doIteration() override;
		void initializeStartLearningAlgoritm() override;
		void initializeResumeLearningAlgoritm() override;
		void initializeLearningAlgoritm() override;
		bool hasLearningSucceeded() override;
		void rateLearning() override;
		void doCalculationAfterLearningProcess() override;
		AbstractLearningResult* getLearningResult() override;
	public:
		/**
		* \brief Creates the supervised learning rule.
		* \param options_ The options which configure the supervised learning rule.
		*/
		AbstractSupervisedLearningRule(AbstractSupervisedLearningRuleOptions& options_);
		/**
		* \brief Creates the supervised learning rule.
		* \param options_ The options which configure the supervised learning rule.
		*/
		AbstractSupervisedLearningRule(AbstractSupervisedLearningRuleOptions* options_);
		// Inherited:
		std::vector<std::string> getDataSetLabels() const override;
	};
}

#include "IO/AbstractSupervisedLearningRuleIO.hpp"

#endif


