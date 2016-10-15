// Includes
#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include <Learning/Evolution/AbstractEvolutionLearningRule.hpp>

namespace LightBulb
{
	void AbstractEvolutionTrainingPlan::fillDefaultLearningRuleOptions(AbstractEvolutionLearningRuleOptions* options)
	{
		AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
		options->world = world.get();
	}

	AbstractEvolutionTrainingPlan::AbstractEvolutionTrainingPlan()
	{
		world = nullptr;
	}

	void AbstractEvolutionTrainingPlan::initializeStart()
	{
		world.reset(createWorld());
	}

	AbstractEvolutionWorld* AbstractEvolutionTrainingPlan::getWorld()
	{
		return world.get();
	}

	void AbstractEvolutionTrainingPlan::setWorld(AbstractEvolutionWorld* world_)
	{
		world.reset(world_);
	}
}