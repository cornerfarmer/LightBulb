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

	class AbstractReinforcementTrainingPlan : public AbstractLearningRuleTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractReinforcementTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractReinforcementTrainingPlan& trainingPlan);
	protected:
		std::unique_ptr<AbstractReinforcementWorld> world;
		virtual AbstractReinforcementWorld* createWorld() = 0;
		void fillDefaultLearningRuleOptions(AbstractReinforcementLearningRuleOptions& options) const;
	public:
		AbstractReinforcementTrainingPlan();
		void initializeStart() override;
		AbstractReinforcementWorld& getWorld();
		void setWorld(AbstractReinforcementWorld& network_);
	};
}

#include "IO/AbstractReinforcementTrainingPlanIO.hpp"

#endif
