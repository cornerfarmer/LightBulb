// Includes
#include "TrainingPlans/AbstractReinforcementTrainingPlan.hpp"
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"

namespace LightBulb
{
	void AbstractReinforcementTrainingPlan::fillDefaultLearningRuleOptions(AbstractReinforcementLearningRuleOptions& options) const
	{
		AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
		options.world = world.get();
	}

	AbstractReinforcementTrainingPlan::AbstractReinforcementTrainingPlan()
	{
		world = nullptr;
	}

	void AbstractReinforcementTrainingPlan::initializeStart()
	{
		world.reset(createWorld());
	}

	AbstractReinforcementWorld& AbstractReinforcementTrainingPlan::getWorld()
	{
		return *world.get();
	}

}