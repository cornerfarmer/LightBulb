// Includes
#include "TrainingPlans/AbstractReinforcementTrainingPlan.hpp"
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"

void AbstractReinforcementTrainingPlan::fillDefaultLearningRuleOptions(AbstractReinforcementLearningRuleOptions* options)
{
	AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
	options->world = world.get();
}

AbstractReinforcementTrainingPlan::AbstractReinforcementTrainingPlan()
{
	world = NULL;
}

void AbstractReinforcementTrainingPlan::initializeStart()
{
	world.reset(createWorld());
}

AbstractReinforcementWorld* AbstractReinforcementTrainingPlan::getWorld()
{
	return world.get();
}

void AbstractReinforcementTrainingPlan::setWorld(AbstractReinforcementWorld* world_)
{
	world.reset(world_);
}
