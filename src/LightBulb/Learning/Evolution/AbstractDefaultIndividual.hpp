#pragma once

#ifndef _ABSTRACTDEFAULTINDIVIDUAL_H_
#define _ABSTRACTDEFAULTINDIVIDUAL_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractIndividual.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class RecurrentFeedForwardNetworkTopologyOptions;
	class AbstractEvolutionWorld;
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
		 * \brief Stores the last ouput of the neural network.
		 */
		std::vector<double> lastOutput;
		/**
		* \brief Stores the last input of the neural network.
		*/
		std::vector<double> lastInput;
		/**
		 * \brief Constructs the lastOutput vector depending on the network sizes.
		 */
		void buildOutputBuffer();
	protected:
		/**
		 * \brief The NN of the individual
		 */
		std::unique_ptr<NeuralNetwork> neuralNetwork;
		/**
		 * \brief The world which contains this individual
		 */
		AbstractEvolutionWorld* world;
		/**
		 * \brief Returns the input for the neural network.
		 * \param input A vector where the input should be stored in.
		 */
		virtual void getNNInput(std::vector<double>& input) = 0;
		/**
		 * \brief Interprets and acts depending on the given NN output
		 * \param output The output of the network.
		 */
		virtual void interpretNNOutput(std::vector<double>& output) = 0;
		/**
		 * \brief Builds the neural network from the given options.
		 * \param options The topology options.
		 */
		void buildNeuralNetwork(FeedForwardNetworkTopologyOptions &options);
	public:
		/**
		 * \brief Creates a new individual in the given world.
		 * \param world The world which should contain the individual.
		 */
		AbstractDefaultIndividual(AbstractEvolutionWorld& world);
		AbstractDefaultIndividual() = default;
		// Inherited:
		void doNNCalculation() override;
		AbstractNeuralNetwork& getNeuralNetwork() override;
		void resetNN() override;
		AbstractIndividual* clone(bool addToWorld = true) const override;
	};
}

#include "IO/AbstractDefaultIndividualIO.hpp"

#endif
