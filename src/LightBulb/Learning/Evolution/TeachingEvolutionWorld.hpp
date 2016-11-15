#pragma once

#ifndef _TEACHINGEVOLUTIONWORLD_H_
#define _TEACHINGEVOLUTIONWORLD_H_

// Library Includes
#include <vector>
#include <map>
// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractEvolutionObject;
	class AbstractTeacher;

#define DATASET_TEACHING_ERROR "Teaching error"
#define DATASET_WEIGHTDECAY_ERROR "Weigth decay error"

	/**
	 * \brief A world which makes it possible to combine the evolution world with classic superives learning.
	 * \details Every evolution objects simply tries to minimize the teaching error.
	 */
	class TeachingEvolutionWorld : public AbstractSimpleEvolutionWorld
	{
	protected:
		/**
		 * \brief Contains the given teacher.
		 */
		AbstractTeacher* teacher;
		/**
		 * \brief Contains the given network options for new evolution objects.
		 */
		FeedForwardNetworkTopologyOptions networkOptions;
		// Inherited
		AbstractEvolutionObject* createNewObject() override;
	public:
		/**
		 * \brief Creates a new teaching evolution world.
		 * \param teacher_ The teacher which contains the learning goals.
		 * \param networkOptions_ The network options which should be used.
		 */
		TeachingEvolutionWorld(AbstractTeacher* teacher_, FeedForwardNetworkTopologyOptions& networkOptions_);
		TeachingEvolutionWorld() = default;
		/**
		 * \brief Returns teh used teacher.
		 * \return The teacher which contains the learning goals.
		 */
		AbstractTeacher& getTeacher() const;
		// Inherited:
		bool doSimulationStep() override;
		std::vector<std::string> getDataSetLabels() const override;
		double getScore(const AbstractEvolutionObject& object) const override;
	};
}

USE_EXISTING_PARENT_SERIALIZATION(LightBulb::TeachingEvolutionWorld, LightBulb::AbstractSimpleEvolutionWorld, LightBulb::AbstractEvolutionWorld, LightBulb)

#endif
