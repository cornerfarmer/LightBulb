#pragma once

#ifndef _ABSTRACTCOEVOLUTIONEVOLUTIONTRAININGPLAN_H_
#define _ABSTRACTCOEVOLUTIONEVOLUTIONTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

// Library includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	struct AbstractEvolutionLearningRuleOptions;
	struct BipartiteEvolutionLearningRuleOptions;
	struct EvolutionLearningRuleOptions;
	/**
	* \brief Describes a training plan which uses coevolution learning.
	*/
	class AbstractCoevolutionTrainingPlan : public AbstractEvolutionTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractCoevolutionTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractCoevolutionTrainingPlan& trainingPlan);
	protected:
		/**
		* \brief The parasite evolution world which is used.
		*/
		std::unique_ptr<AbstractEvolutionWorld> parasiteWorld;
		/**
		* \brief Creates the parasite evolution world.
		* \return The new parasite world.
		*/
		virtual AbstractEvolutionWorld* createParasiteWorld() = 0;
		/**
		* \brief Fills all learning rule options which are the same for all coevolution learning rule training plans.
		* \param options The options to fill.
		*/
		void fillDefaultLearningRuleOptions(BipartiteEvolutionLearningRuleOptions& options) const;
		/**
		* \brief Fills all learning rule options which are the same for the first evolution learning rule.
		* \param options The options to fill.
		*/
		void fillDefaultEvolutionLearningRule1Options(EvolutionLearningRuleOptions& options) const;
		/**
		* \brief Fills all learning rule options which are the same for the second evolution learning rule.
		* \param options The options to fill.
		*/
		void fillDefaultEvolutionLearningRule2Options(EvolutionLearningRuleOptions& options) const;
	public:
		/**
		 * \brief Returns the parasite evolution world.
		 * \return The world.
		 */
		AbstractEvolutionWorld& getParasiteWorld();
		// Inherited:
		void initializeStart() override;
	};
}

#include "IO/AbstractCoevolutionTrainingPlanIO.hpp"

#endif
