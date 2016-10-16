// Includes
#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>

namespace LightBulb
{
	void AbstractCoevolutionTrainingPlan::fillDefaultLearningRuleOptions(BipartiteEvolutionLearningRuleOptions* options) const
	{
		AbstractEvolutionTrainingPlan::fillDefaultLearningRuleOptions(options);
	}

	void AbstractCoevolutionTrainingPlan::fillDefaultEvolutionLearningRule1Options(EvolutionLearningRuleOptions* options) const
	{
		options->world = world.get();
	}

	void AbstractCoevolutionTrainingPlan::fillDefaultEvolutionLearningRule2Options(EvolutionLearningRuleOptions* options) const
	{
		options->world = parasiteWorld.get();
	}

	void AbstractCoevolutionTrainingPlan::initializeStart()
	{
		parasiteWorld.reset(createParasiteWorld());
		AbstractEvolutionTrainingPlan::initializeStart();
	}

	AbstractEvolutionWorld* AbstractCoevolutionTrainingPlan::getParasiteWorld()
	{
		return parasiteWorld.get();
	}

	void AbstractCoevolutionTrainingPlan::setParasiteWorld(AbstractEvolutionWorld* world_)
	{
		parasiteWorld.reset(world_);
	}
}