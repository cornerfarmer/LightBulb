#pragma once

#ifndef _TEACHINGEVOLUTIONENVIRONMENT_H_
#define _TEACHINGEVOLUTIONENVIRONMENT_H_

// Library Includes
#include <vector>
#include <map>
// Include
#include "LightBulb/Learning/Evolution/AbstractSimpleEvolutionEnvironment.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractIndividual;
	class AbstractTeacher;

#define DATASET_TEACHING_ERROR "Teaching error"
#define DATASET_WEIGHTDECAY_ERROR "Weigth decay error"

	/**
	 * \brief A environment which makes it possible to combine the evolution environment with classic superives learning.
	 * \details Every individuals simply tries to minimize the teaching error.
	 */
	class TeachingEvolutionEnvironment : public AbstractSimpleEvolutionEnvironment
	{
	protected:
		/**
		 * \brief Contains the given teacher.
		 */
		AbstractTeacher* teacher;
		/**
		 * \brief Contains the given network options for new individuals.
		 */
		FeedForwardNetworkTopologyOptions networkOptions;
		// Inherited
		AbstractIndividual* createNewIndividual() override;
	public:
		/**
		 * \brief Creates a new teaching evolution environment.
		 * \param teacher_ The teacher which contains the learning goals.
		 * \param networkOptions_ The network options which should be used.
		 */
		TeachingEvolutionEnvironment(AbstractTeacher* teacher_, FeedForwardNetworkTopologyOptions& networkOptions_);
		TeachingEvolutionEnvironment() = default;
		/**
		 * \brief Returns teh used teacher.
		 * \return The teacher which contains the learning goals.
		 */
		AbstractTeacher& getTeacher() const;
		// Inherited:
		void doSimulationStep() override;
		std::vector<std::string> getDataSetLabels() const override;
		void getFitness(const AbstractIndividual& individual, LightBulb::Scalar<>& fitness) const override;
	};
}

USE_EXISTING_PARENT_SERIALIZATION(LightBulb::TeachingEvolutionEnvironment, LightBulb::AbstractSimpleEvolutionEnvironment, LightBulb::AbstractEvolutionEnvironment, LightBulb)

#endif
