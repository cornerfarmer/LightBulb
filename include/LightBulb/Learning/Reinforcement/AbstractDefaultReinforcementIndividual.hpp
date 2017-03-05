#pragma once

#ifndef _AbstractDefaultReinforcementIndividual_H_
#define _AbstractDefaultReinforcementIndividual_H_

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

	class AbstractDefaultReinforcementIndividual : public AbstractReinforcementIndividual
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractDefaultReinforcementIndividual& individual);
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
		// Inherited:
		void doNNCalculation() override;
	public:
		~AbstractDefaultReinforcementIndividual();
		/**
		 * \brief Creates the reinforcement environment.
		 * \param options The options which describe the network. 
		 * \param epsilonGreedly True, if the environment should act greedly when picking actions.
		 * \param epsilon The epsilon value when acting epsilon greedly.
		 */
		AbstractDefaultReinforcementIndividual(AbstractReinforcementEnvironment* environment_, FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly = false, double epsilon = 0.1);
		AbstractDefaultReinforcementIndividual();
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

#include "LightBulb/IO/AbstractDefaultReinforcementIndividualIO.hpp"

#endif
