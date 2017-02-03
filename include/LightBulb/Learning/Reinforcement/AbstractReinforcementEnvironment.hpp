#pragma once

#ifndef _ABSTRACTREINFORCEMENTENVIRONMENT_H_
#define _ABSTRACTREINFORCEMENTENVIRONMENT_H_

// Library Includes
#include <vector>
#include <memory>

// Includes
#include "LightBulb/Random/AbstractRandomGeneratorUser.hpp"

namespace LightBulb
{
	// Forward declarations
	struct FeedForwardNetworkTopologyOptions;
	struct LearningState;
	class NeuralNetwork;
	/**
	 * \brief Describes the environment where the reinforcement learning process takes places.
	 */
	class AbstractReinforcementEnvironment : public virtual AbstractRandomGeneratorUser
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractReinforcementEnvironment& environment);
	private:
		/**
		 * \brief Contains the last output of the neural network.
		 */
		std::vector<double> lastOutput;
		/**
		* \brief Contains which actions where taken after the last output.
		*/
		std::vector<bool> lastBooleanOutput;
		/**
		* \brief Contains the last input of the neural network.
		*/
		std::vector<double> lastInput;
		/**
		 * \brief True, if the environment should act greedly when picking actions.
		 */
		bool epsilonGreedly = false;
		/**
		 * \brief The epsilon value when acting epsilon greedly.
		 */
		double epsilon;
		/**
		 * \brief True, if actions should be taken randomly.
		 */
		bool useStochasticActionDecision;
		/**
		 * \brief Builds the output buffer depending on the current network.
		 */
		void buildOutputBuffer();
		/**
		 * \brief Builds the neural network.
		 * \param options The options which describe the network.
		 */
		void buildNeuralNetwork(FeedForwardNetworkTopologyOptions &options);
	protected:
		/**
		 * \brief Points to the learning state of the learning rule.
		 */
		LearningState* learningState;
		/**
		 * \brief The neural network which should be trained.
		 */
		std::unique_ptr<NeuralNetwork> neuralNetwork;
		/**
		 * \brief Interprets the given neural network output and acts depending on it.
		 * \param output The actions which were taken by the network.
		 */
		virtual void interpretNNOutput(std::vector<bool>& output) = 0;
	public:
		/**
		 * \brief Returns the new input for the neural network.
		 * \param input The vector were the input should be stored in.
		 */
		virtual void getNNInput(std::vector<double>& input) = 0;
		/**
		 * \brief Executes the neural network calculation.
		 */
		void doNNCalculation();
		~AbstractReinforcementEnvironment();
		/**
		 * \brief Creates the reinforcement environment.
		 * \param options The options which describe the network. 
		 * \param epsilonGreedly True, if the environment should act greedly when picking actions.
		 * \param epsilon The epsilon value when acting epsilon greedly.
		 */
		AbstractReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly = false, double epsilon = 0.1);
		AbstractReinforcementEnvironment();
		/**
		* \brief Executes one simulation step.
		* \return Returns the reward gained after that step.
		*/
		virtual double doSimulationStep() = 0;
		/**
		* \brief Initializes the environment before the learning starts.
		*/
		virtual void initializeForLearning();
		/**
		 * \brief Can be used to rate the current AI for debugging purposes.
		 * \return The rating.
		 */
		virtual int rate() { return 0; };
		/**
		 * \brief Returns the neural network.
		 * \return The neural network.
		 */
		NeuralNetwork& getNeuralNetwork();
		/**
		 * \brief Sets a new epsilon value.
		 * \param newEpsilon The new epsilon value.
		 */
		void setEpsilon(double newEpsilon);
		/**
		 * \brief Returns the epsilon value.
		 * \return The epsilon value.
		 */
		double getEpsilon();
		/**
		 * \brief Sets the learning state.
		 * \param learningState_ The learning state.
		 */
		void setLearningState(LearningState& learningState_);
		/**
		* \brief Returns a vector of all data set labels which are available in the learning state of this learning rule.
		* \return The labels of all available data sets.
		*/
		virtual std::vector<std::string> getDataSetLabels() const;
		/**
		 * \brief Returns the last chosen actions of the network.
		 * \return A vector of bools which tell per actions if they were taken.
		 */
		std::vector<bool>& getLastBooleanOutput();
		/**
		 * \brief Returns if the environment is in a terminal state.
		 * \return True, if the environment is in a terminal state.
		 */
		virtual bool isTerminalState() = 0;
		/**
		 * \brief Sets, if actions should be taken randomly. 
		 * \param useStochasticActionDecision_ True, if actions should be taken randomly. 
		 */
		void setStochasticActionDecision(bool useStochasticActionDecision_);
	};
}

#include "LightBulb/IO/AbstractReinforcementEnvironmentIO.hpp"

#endif
