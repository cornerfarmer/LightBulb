#pragma once

#ifndef _DEFAULTREINFORCEMENTINDIVIDUAL_H_
#define _DEFAULTREINFORCEMENTINDIVIDUAL_H_

// Library Includes
#include <vector>
#include <memory>

// Includes
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"
#include "AbstractReinforcementIndividual.hpp"

namespace LightBulb
{
	// Forward declarations
	struct FeedForwardNetworkTopologyOptions;
	struct LearningState;
	class NeuralNetwork;
	class Kernel;
	class AbstractReinforcementEnvironment;
	/**
	 * \brief Describes the environment where the reinforcement learning process takes places.
	 */
	class DefaultReinforcementIndividual : public AbstractReinforcementIndividual
	{
		template <class Archive>
		friend void serialize(Archive& archive, DefaultReinforcementIndividual& individual);
	private:
		std::unique_ptr<Kernel> setBooleanOutputNonGreedyStochasticKernel;
		std::unique_ptr<Kernel> setBooleanOutputNonGreedyKernel;
		std::unique_ptr<Kernel> setBooleanOutputRandKernel;
		std::unique_ptr<Kernel> setBooleanOutputBestKernel;
		/**
		* \brief Contains which actions where taken after the last output.
		*/
		Vector<char> lastBooleanOutput;
		/**
		* \brief Contains the last input of the neural network.
		*/
		Vector<> lastInput;
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
		AbstractReinforcementEnvironment* environment;
		/**
		 * \brief The neural network which should be trained.
		 */
		std::unique_ptr<NeuralNetwork> neuralNetwork;
		/**
		 * \brief Interprets the given neural network output and acts depending on it.
		 * \param output The actions which were taken by the network.
		 */
		virtual void interpretNNOutput(Vector<char>& output);
		// Inherited:
		void doNNCalculation() override;
	public:
		/**
		 * \brief Returns the new input for the neural network.
		 * \param input The vector were the input should be stored in.
		 */
		virtual void getNNInput(Vector<>& input);
		~DefaultReinforcementIndividual();
		/**
		 * \brief Creates the reinforcement environment.
		 * \param options The options which describe the network. 
		 * \param epsilonGreedly True, if the environment should act greedly when picking actions.
		 * \param epsilon The epsilon value when acting epsilon greedly.
		 */
		DefaultReinforcementIndividual(AbstractReinforcementEnvironment* environment_, FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly = false, double epsilon = 0.1);
		DefaultReinforcementIndividual();
		// Inherited:
		void initializeKernels() override;
		void initializeForLearning() override;
		int rate() override { return 0; };
		NeuralNetwork& getNeuralNetwork() override;
		void setEpsilon(double newEpsilon) override;
		double getEpsilon() override;
		const Vector<char>& getLastBooleanOutput() const override;
		const Vector<>& getLastInput() const override;
		void setStochasticActionDecision(bool useStochasticActionDecision_) override;
		void setCalculatorType(const CalculatorType& calculatorType) override;
	};
}

#include "LightBulb/IO/DefaultReinforcementIndividualIO.hpp"

#endif
