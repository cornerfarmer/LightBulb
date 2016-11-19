#pragma once

#ifndef _TEACHEDINDIVIDUAL_H_
#define _TEACHEDINDIVIDUAL_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractIndividual.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class TeachingEvolutionWorld;
	class FeedForwardNetworkTopologyOptions;
	/**
	 * \brief A individual used in the TeachingEvolutionWorld.
	 */
	class TeachedIndividual : public AbstractIndividual
	{
		template <class Archive>
		friend void save(Archive& archive, TeachedIndividual const& individual);
		template <class Archive>
		friend void load(Archive& archive, TeachedIndividual& individual);
	protected:
		/**
		 * \brief The corresponding world.
		 */
		TeachingEvolutionWorld* teachingEvolutionWorld;
		/**
		 * \brief The used network
		 */
		std::unique_ptr<NeuralNetwork> neuralNetwork;
		/**
		 * \brief The current total error.
		 */
		double currentTotalError;
		/**
		 * \brief The current teaching error.
		 */
		double currentTeachingError;
		/**
		 * \brief The current weight decay error.
		 */
		double currentWeightDecayError;
	public:
		/**
		 * \brief Create a new individual in the given world and with a NN built with the given network options.
		 * \param teachingEvolutionWorld_ The world which should contain the individual.
		 * \param options The feed forward network options.
		 */
		TeachedIndividual(TeachingEvolutionWorld& teachingEvolutionWorld_, FeedForwardNetworkTopologyOptions& options);
		TeachedIndividual() = default;
		/**
		 * \brief Returns the current total error.
		 * \return The current total error.
		 */
		double getCurrentTotalError() const;
		/**
		 * \brief Returns the current teaching error.
		 * \return The current teaching error.
		 */
		double getCurrentTeachingError() const;
		/**
		 * \brief Returns the current weight decay error.
		 * \return The current weight decay error.
		 */
		double getCurrentWeightDecayError() const;
		// Inherited:
		void doNNCalculation() override;
		void resetNN() override;
		AbstractNeuralNetwork& getNeuralNetwork() override;
		AbstractIndividual* clone(bool addToWorld = true) const override;
	};
}

#include "IO/TeachedIndividualIO.hpp"

#endif
