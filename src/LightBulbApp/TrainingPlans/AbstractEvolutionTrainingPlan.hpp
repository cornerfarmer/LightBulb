#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLAN_H_
#define _ABSTRACTEVOLUTIONTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

// Library includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	struct AbstractEvolutionLearningRuleOptions;
	/**
	* \brief Describes a training plan which uses evolution learning.
	*/
	class AbstractEvolutionTrainingPlan : public AbstractLearningRuleTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractEvolutionTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractEvolutionTrainingPlan& trainingPlan);
	protected:
		/**
		 * \brief The evolution world which is used.
		 */
		std::unique_ptr<AbstractEvolutionWorld> world;
		/**
		 * \brief Creates the evolution world.
		 * \return The new world.
		 */
		virtual AbstractEvolutionWorld* createWorld() = 0;
		/**
		* \brief Fills all learning rule options which are the same for all evolution learning rule training plans.
		* \param options The options to fill.
		*/
		void fillDefaultLearningRuleOptions(AbstractEvolutionLearningRuleOptions& options) const;
	public:
		/**
		 * \brief Creates the evolution training plan.
		 */
		AbstractEvolutionTrainingPlan();
		/**
		 * \brief Returns the evolution world.
		 * \return The world.
		 */
		AbstractEvolutionWorld& getWorld();
		// Inherited:
		void initializeStart() override;
	};
}

#include "IO/AbstractEvolutionTrainingPlanIO.hpp"

#endif
