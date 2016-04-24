// Includes
#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>

void AbstractCoevolutionTrainingPlan::fillDefaultLearningRuleOptions(BipartiteEvolutionLearningRuleOptions* options)
{
	AbstractEvolutionTrainingPlan::fillDefaultLearningRuleOptions(options);
}

void AbstractCoevolutionTrainingPlan::fillDefaultEvolutionLearningRule1Options(EvolutionLearningRuleOptions* options)
{
	options->world = world.get();
}

void AbstractCoevolutionTrainingPlan::fillDefaultEvolutionLearningRule2Options(EvolutionLearningRuleOptions* options)
{
	options->world = parasiteWorld.get();
}

void AbstractCoevolutionTrainingPlan::initializeStart()
{
	AbstractEvolutionTrainingPlan::initializeStart();
	parasiteWorld.reset(createParasiteWorld());
}

AbstractEvolutionWorld* AbstractCoevolutionTrainingPlan::getParasiteWorld()
{
	return parasiteWorld.get();
}

void AbstractCoevolutionTrainingPlan::setParasiteWorld(AbstractEvolutionWorld* world_)
{
	parasiteWorld.reset(world_);
}
