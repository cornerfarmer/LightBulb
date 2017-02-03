#pragma once

#ifndef _TEACHEDINDIVIDUAL_H_
#define _TEACHEDINDIVIDUAL_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
// TODO: Remove
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class TeachingEvolutionEnvironment;
	class FeedForwardNetworkTopologyOptions;
	class NeuralNetwork;
	/**
	 * \brief A individual used in the TeachingEvolutionEnvironment.
	 */
	class TeachedIndividual : public AbstractIndividual
	{
		template <class Archive>
		friend void save(Archive& archive, TeachedIndividual const& individual);
		template <class Archive>
		friend void load(Archive& archive, TeachedIndividual& individual);
	protected:
		/**
		 * \brief The corresponding environment.
		 */
		TeachingEvolutionEnvironment* teachingEvolutionEnvironment;
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
		 * \brief Create a new individual in the given environment and with a NN built with the given network options.
		 * \param teachingEvolutionEnvironment_ The environment which should contain the individual.
		 * \param options The feed forward network options.
		 */
		TeachedIndividual(TeachingEvolutionEnvironment& teachingEvolutionEnvironment_, FeedForwardNetworkTopologyOptions& options);
		TeachedIndividual();
		~TeachedIndividual();
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
		AbstractIndividual* clone(bool addToEnvironment = true) const override;
	};
}

#include "LightBulb/IO/TeachedIndividualIO.hpp"

#endif
