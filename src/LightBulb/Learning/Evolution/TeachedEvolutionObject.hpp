#pragma once

#ifndef _TEACHEDEVOLUTIONOBJECT_H_
#define _TEACHEDEVOLUTIONOBJECT_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class TeachingEvolutionWorld;
	class FeedForwardNetworkTopologyOptions;
	/**
	 * \brief A evolution object used in the TeachingEvolutionWorld.
	 */
	class TeachedEvolutionObject : public AbstractEvolutionObject
	{
		template <class Archive>
		friend void save(Archive& archive, TeachedEvolutionObject const& object);
		template <class Archive>
		friend void load(Archive& archive, TeachedEvolutionObject& object);
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
		 * \brief Create a new evolution object in the given world and with a NN built with the given network options.
		 * \param teachingEvolutionWorld_ The world which should contain the object.
		 * \param options The feed forward network options.
		 */
		TeachedEvolutionObject(TeachingEvolutionWorld& teachingEvolutionWorld_, FeedForwardNetworkTopologyOptions& options);
		TeachedEvolutionObject() = default;
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
		AbstractEvolutionObject* clone(bool addToWorld = true) const override;
	};
}

#include "IO/TeachedEvolutionObjectIO.hpp"

#endif
