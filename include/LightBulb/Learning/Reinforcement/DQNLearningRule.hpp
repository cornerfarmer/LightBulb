#pragma once

#ifndef _DQNLEARNINGRULE_H_
#define _DQNLEARNINGRULE_H_

// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentLearningRule.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "LightBulb/Teaching/TeachingInput.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"

// Library Includes
#include <vector>
#include "TransitionStorage.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;
	class Kernel;

#define DATA_SET_TRAINING_ERROR "Training error"
#define DATA_SET_EPSILON "Epsilon"
#define DATA_SET_Q_VALUE "Q-Value"
#define DATA_SET_AVG_Q_VALUE "Avg. Q-Value"

	/**
	* \brief All options for the DQNLearningRule.
	*/
	struct DQNLearningRuleOptions : public AbstractReinforcementLearningRuleOptions
	{
		/**
		* \brief The amount of training samples used in a minibatch.
		* \details Default value: 32
		*/
		int minibatchSize;
		/**
		* \brief The maximum number of stored transitions in the replay memory.
		* \details Default value: 1000000
		*/
		int replayMemorySize;
		/**
		* \brief After how many iterations the target network should be updated.
		* \details Default value: 10000
		*/
		int targetNetworkUpdateFrequency;
		/**
		* \brief The discount factor for the q learning part.
		* \details Default value: 0.99
		*/
		double discountFactor;
		/**
		* \brief The epsilon value at the beginning.
		* \details Default value: 1
		*/
		double initialExploration;
		/**
		* \brief The final epsilon value to use after the finalExplorationFrame.
		* \details Default value: 0.1
		*/
		double finalExploration;
		/**
		* \brief How long the transition between the initialExploration and the finalExploration epsilon value should take.
		* \details Default value: 1000000
		*/
		int finalExplorationFrame;
		/**
		 * \brief After how many iterations the learning process should start.
		 * \details Default value: 50000
		 */
		int replayStartSize;
		/**
		 * \brief True, if after the replay memory is full, old transition should be replaced.
		 * \details Default value: true
		 */
		bool replaceStoredTransitions;
		/**
		 * \brief The options for the gradient descent learning part.
		 * \details Default values:
		 * * maxIterationsPerTry: 1
		 * * maxTries: 1
		 * * changeWeightsBeforeLearning: false
		 * * offlineLearning: true
		 * * totalErrorGoal: -1
		 * * clipError: true
		 */
		GradientDescentLearningRuleOptions gradientDescentOptions;
		/**
		 * \brief The rms prop options which are used in the gradient descent algorithm
		 * \details Default values:
		 * * learningRate: 0.00025
		 */
		RMSPropLearningRateOptions rmsPropOptions;
		DQNLearningRuleOptions()
		{
			minibatchSize = 32;
			replayMemorySize = 1000000;
			targetNetworkUpdateFrequency = 10000;
			discountFactor = 0.99;
			initialExploration = 1;
			finalExploration = 0.1;
			finalExplorationFrame = 1000000;
			replayStartSize = 50000;
			replaceStoredTransitions = true;

			gradientDescentOptions.maxIterationsPerTry = 1;
			gradientDescentOptions.maxTries = 1;
			gradientDescentOptions.changeWeightsBeforeLearning = false;
			gradientDescentOptions.offlineLearning = true;
			gradientDescentOptions.totalErrorGoal = -1;
			gradientDescentOptions.clipError = true;

			rmsPropOptions.learningRate = 0.00025;
		}
	};
	
	/**
	 * \brief Deep Q-Network learning combines deep neural networks with reinforcement learning.
	 * \details To make the learning process work with non linear function approximators the following methods are used:
	 * * replay memory
	 * * steady/target network
	 * 
	 * The algorithm description can be found in "Playing Atari with deep reinforcement learning" (Mnih et al., 2013)
	 */
	class DQNLearningRule : public AbstractReinforcementLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, DQNLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<DQNLearningRule>;
	private:
		
		std::unique_ptr<Kernel> setTeachingInputKernel;
		
		/**
		 * \brief The number of iterations until learning will start.
		 */
		int waitUntilLearningStarts;
		/**
		 * \brief The current total sum of all error values in this iteration.
		 */
		double currentTotalError;
		/**
		 * \brief The teacher which is used by the gradient descent part.
		 */
		std::unique_ptr<Teacher> teacher;
		/**
		 * \brief The transition memory store.
		 */
		std::shared_ptr<TransitionStorage> transitionStorage;
		/**
		 * \brief The gradient descent learning rule.
		 */
		std::unique_ptr<GradientDescentLearningRule> gradientDescent;
		/**
		 * \brief The steady/target network.
		 */
		std::unique_ptr<AbstractNeuralNetwork> steadyNetwork;
		/**
		 * \brief Temporarily stores the current reward. 
		 */
		Scalar<> reward;
		/**
		 * \brief The current reward sum.
		 */
		Scalar<> totalReward;
		/**
		* \brief Temporarily stores an input vector.
		*/
		Vector<> tmp;
		/**
		* \brief Contains all currently selected teaching lesson inputs.
		*/
		std::vector<TeachingInput<>*> teachingLessonsInputs;
		/**
		* \brief Contains all currently selected teaching lesson patterns.
		*/
		std::vector<Vector<>*> teachingLessonsPatterns;
		/**
		 * \brief The current total sum of all average q values in this iteration.
		 */
		double qAvgSum;
		/**
		 * \brief Initializes the learning rule.
		 * \param options The options to use.
		 */
		void initialize(DQNLearningRuleOptions* options);
	public:
		/**
		 * \brief Executes a mini batch learning iteration.
		 */
		void doSupervisedLearning();
	protected:
		// Inherited:
		void doIteration() override;
		const DQNLearningRuleOptions& getOptions() const override;
		AbstractLearningResult* getLearningResult() override;
	public:
		/**
		* \brief Creates the dqn learning rule.
		* \param options_ The options which configure the dqn learning rule.
		*/
		DQNLearningRule(DQNLearningRuleOptions& options_);
		/**
		* \brief Creates the dqn learning rule.
		* \param options_ The options which configure the dqn learning rule.
		*/
		DQNLearningRule(DQNLearningRuleOptions* options_);
		DQNLearningRule();
		~DQNLearningRule();
		/**
		 * \brief Returns the name of the learning rule.
		 * \return The name.
		 */
		static std::string getName();
		void setTransitionStorage(const std::shared_ptr<TransitionStorage>& transitionStorage);
		// Inherited:
		void initializeTry() override;
		/**
		* \brief Returns the name of the learning rule
		* \return The name
		*/
		std::vector<std::string> getDataSetLabels() const override;
		void refreshSteadyNetwork();
	};
}

#include "LightBulb/IO/DQNLearningRuleIO.hpp"


#endif
