#pragma once

#ifndef _ABSTRACTREINFORCEMENTTRAININGPLAN_H_
#define _ABSTRACTREINFORCEMENTTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"
#include "Learning/Reinforcement/AbstractReinforcementWorld.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	struct AbstractReinforcementLearningRuleOptions;
	/**
	* \brief Describes a training plan which uses reinforcement learning.
	*/
	class AbstractReinforcementTrainingPlan : public AbstractLearningRuleTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractReinforcementTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractReinforcementTrainingPlan& trainingPlan);
	protected:
		/**
		 * \brief The reinforcement world which is used.
		 */
		std::unique_ptr<AbstractReinforcementWorld> world;
		/**
		 * \brief Creates the reinforcement world.
		 * \return The new world.
		 */
		virtual AbstractReinforcementWorld* createWorld() = 0;
		/**
		* \brief Fills all learning rule options which are the same for all reinforcement learning rule training plans.
		* \param options The options to fill.
		*/
		void fillDefaultLearningRuleOptions(AbstractReinforcementLearningRuleOptions& options) const;
	public:
		/**
		 * \brief Creates the reinforcement training plan.
		 */
		AbstractReinforcementTrainingPlan();
		/**
		 * \brief Returns the reinforcement world.
		 * \return The world.
		 */
		AbstractReinforcementWorld& getWorld();
		// Inherited:
		void initializeStart() override;
	};
}

#include "IO/AbstractReinforcementTrainingPlanIO.hpp"

#endif
