#pragma once

#ifndef _POLICYGRADIENTLEARNINGRULE_H_
#define _POLICYGRADIENTLEARNINGRULE_H_

// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"

// Library Includes
#include <vector>
#include "LightBulb/LinearAlgebra/Tensor.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;
	class AbstractGradientCalculation;
	class NeuralNetwork;
	class Kernel;
	/**
	* \brief All options for the PolicyGradientLearningRule.
	*/
	struct PolicyGradientLearningRuleOptions : public AbstractReinforcementLearningRuleOptions
	{/**
		* \brief Determines after how many episodes the gradient descent should be executed.
		* \details Default value: 10
		*/
		int episodeSize;
		/**
		 * \brief Determines the maximum length of an episode.
		 * \details Default value: 1000
		 */
		int maxEpisodeLength;
		/**
		 * \brief Determines after how many episodes the network should be rated (for debugging purposes).
		 * \details Default value: 10
		 */
		int ratingInterval;
		/**
		* \brief Determines after how many iterations the total reward should be logged.
		* \details Default value: 15
		*/
		int logInterval;
		/**
		 * \brief The rmsprop options used in the gradient descent algorithm
		 * \details Default values:
		 * * learningRate: 1e-4
		 */
		RMSPropLearningRateOptions rmsPropLearningRateOptions;
		/**
		* \brief True, if a value function should be used as base.
		* \details Default value: true
		*/
		bool valueFunctionAsBase;
		/**
		* \brief The rmsprop options used in the gradient descent algorithm for optimizing the value function.
		*/
		RMSPropLearningRateOptions valueRmsPropLearningRateOptions;
		PolicyGradientLearningRuleOptions()
		{
			episodeSize = 10000;
			maxEpisodeLength = 1000;
			ratingInterval = 10;
			logInterval = 15;
			rmsPropLearningRateOptions.learningRate = 1e-4;
			valueFunctionAsBase = true;
			valueRmsPropLearningRateOptions.learningRate = 1e-4;
		}
	};

	#define DATA_SET_ERROR_AVG "Error avg"
	#define DATA_SET_VALUE_ERROR_AVG "Value error avg"

	/**
	 * \brief A reinforcement learning method which directly learns the policy.
	 */
	class PolicyGradientLearningRule : public AbstractReinforcementLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, PolicyGradientLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<PolicyGradientLearningRule>;
	private:
		std::unique_ptr<Kernel> getErrorVectorKernel;
		std::unique_ptr<Kernel> computeNextRecordIndexKernel;
		std::unique_ptr<Kernel> computeRewardsKernel;
		std::unique_ptr<Kernel> computeNextRecordStartKernel;
		std::unique_ptr<Kernel> computeGradientsKernel;
		/**
		 * \brief The state memory.
		 */
		Matrix<> stateRecord;
		/**
		 * \brief The terminal state memory.
		 */
		Vector<char> isTerminalStateRecord;
		/**
		 * \brief The reward memory.
		 */
		Vector<> rewardRecord;
		/**
		 * \brief Temporarily stores isTerminalState.
		 */
		Scalar<char> isTerminalState;
		/**
		 * \brief Temporarily stores an input vector.
		 */
		Vector<> tmp;
		/**
		* \brief Temporarily stores an error vector.
		*/
		Vector<> errorVector;
		/**
		* \brief Temporarily stores the reward.
		*/
		Scalar<> reward;
		/**
		* \brief Temporarily stores the total reward.
		*/
		Scalar<> totalReward;
		/**
		* \brief The gradient memory.
		*/
		std::vector<Tensor<>> gradientRecord;
		/**
		* \brief The current total gradient.
		*/
		std::vector<Matrix<>> tmpGradient;
		/**
		* \brief The current total gradient.
		*/
		std::vector<Matrix<>> gradient;
		/**
		 * \brief The gradient calculation algorithm used for the policy function.
		 */
		std::unique_ptr<AbstractGradientCalculation> gradientCalculation;
		/**
		* \brief The gradient descent algorithm used for the policy function.
		*/
		std::unique_ptr<AbstractGradientDescentAlgorithm> gradientDescentAlgorithm;
		/**
		* \brief The gradient calculation algorithm used for the value function.
		*/
		std::unique_ptr<AbstractGradientCalculation> valueFunctionGradientCalculation;
		/**
		* \brief The gradient descent algorithm used for the value function.
		*/
		std::unique_ptr<AbstractGradientDescentAlgorithm> valueFunctionGradientDescentAlgorithm;
		/**
		 * \brief The value function network which can act as a base.
		 */
		std::unique_ptr<NeuralNetwork> valueFunctionNetwork;
		/**
		 * \brief The current sum of all error values.
		 */
		double errorSum;
		/**
		* \brief The current sum of all error values of the value function learning process.
		*/
		double valueErrorSum;
		/**
		 * \brief The index where the record starts.
		 */
		Scalar<int> recordStart;
		/**
		* \brief The index where the next record should be stored.
		*/
		Scalar<int> nextRecordIndex;
		/**
		* \brief Temporarily stores the last relevant index.
		*/
		Scalar<int> lastRelevantIndex;
		/**
		 * \brief A step counter used for calculating the average error with errorSum.
		 */
		int errorSteps;
		/**
		* \brief A step counter used for calculating the value average error with valueErrorSum.
		*/
		int valueErrorSteps;
		/**
		 * \brief Adds the total gradient to the network topology.
		 * \param networkTopology The network topology to use.
		 */
		void addGradients(AbstractNetworkTopology& networkTopology);
		/**
		 * \brief Computes the gradient for the last episode and adds it to the total gradient sum.
		 */
		void computeGradients();
		/**
		* \brief Initializes the learning rule.
		* \param options The options to use.
		*/
		void initialize(PolicyGradientLearningRuleOptions& options);
		/**
		 * \brief Records the current step.
		 * \param networkTopology The network topology which was used.
		 */
		void recordStep(AbstractNetworkTopology& networkTopology, Scalar<>& reward);
		/**
		 * \brief Returns the total buffer size.
		 * \return The total buffer size.
		 */
		int getBufferSize();
		/**
		 * \brief Calculates the error vector.
		 * \param networkTopology The network topology to use.
		 * \param errorVector The vector where the error vector should be stored.
		 */
		void getErrorVector(AbstractNetworkTopology& networkTopology, Vector<>& errorVector);
	protected:
		// Inherited:
		void doIteration() override;
		const PolicyGradientLearningRuleOptions& getOptions() const override;
		void doCalculationAfterLearningProcess() override;
		AbstractLearningResult* getLearningResult() override;
		void initializeLearningAlgoritm() override;
	public:
		/**
		* \brief Creates the policy gradient learning rule.
		* \param options_ The options which configure the policy gradient learning rule.
		*/
		PolicyGradientLearningRule(PolicyGradientLearningRuleOptions& options_);
		/**
		* \brief Creates the policy gradient learning rule.
		* \param options_ The options which configure the policy gradient learning rule.
		*/
		PolicyGradientLearningRule(PolicyGradientLearningRuleOptions* options_);
		PolicyGradientLearningRule();
		~PolicyGradientLearningRule();
		/**
		* \brief Returns the name of the learning rule.
		* \return The name.
		*/
		static std::string getName();
		// Inherited:
		void initializeTry() override;
		std::vector<std::string> getDataSetLabels() const override;
	};
}

#include "LightBulb/IO/PolicyGradientLearningRuleIO.hpp"

#endif
