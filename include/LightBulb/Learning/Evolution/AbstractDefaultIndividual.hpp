#pragma once

#ifndef _ABSTRACTDEFAULTINDIVIDUAL_H_
#define _ABSTRACTDEFAULTINDIVIDUAL_H_

// Library Includes
#include <memory>

// Includes
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class RecurrentFeedForwardNetworkTopologyOptions;
	class AbstractEvolutionEnvironment;
	class AbstractNeuronDescriptionFactory;
	struct FeedForwardNetworkTopologyOptions;
	/**
	 * \brief This class is simplification of the AbstractIndividual class.
	 * \details It decreases the work you have to do for your individual class, but also decreases your possibilities.
	 * Nevertheless this class can be used in the most of all cases. 
	 * It manages the neural network, so you only have to set input and interpret output of the network.
	 */
	class AbstractDefaultIndividual : public AbstractIndividual
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractDefaultIndividual const& individual);
		template <class Archive>
		friend void load(Archive& archive, AbstractDefaultIndividual& individual);
	private:
		/**
		* \brief Stores the last input of the neural network.
		*/
		Vector<> lastInput;
	protected:
		/**
		 * \brief The NN of the individual
		 */
		std::unique_ptr<NeuralNetwork> neuralNetwork;
		/**
		 * \brief The environment which contains this individual
		 */
		AbstractEvolutionEnvironment* environment;
		/**
		 * \brief Returns the input for the neural network.
		 * \param input A vector where the input should be stored in.
		 */
		virtual void getNNInput(Vector<>& input) = 0;
		/**
		 * \brief Interprets and acts depending on the given NN output
		 * \param output The output of the network.
		 */
		virtual void interpretNNOutput(const Vector<>& output) = 0;
		/**
		 * \brief Builds the neural network from the given options.
		 * \param options The topology options.
		 */
		void buildNeuralNetwork(FeedForwardNetworkTopologyOptions &options);
	public:
		/**
		 * \brief Creates a new individual in the given environment.
		 * \param environment The environment which should contain the individual.
		 */
		AbstractDefaultIndividual(AbstractEvolutionEnvironment& environment);
		AbstractDefaultIndividual() = default;
		// Inherited:
		void doNNCalculation() override;
		AbstractNeuralNetwork& getNeuralNetwork() override;
		void resetNN() override;
		AbstractIndividual* clone(bool addToEnvironment = true) const override;
	};
}

#include "LightBulb/IO/AbstractDefaultIndividualIO.hpp"

#endif
