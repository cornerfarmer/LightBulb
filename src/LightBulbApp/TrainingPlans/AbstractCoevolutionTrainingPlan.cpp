// Includes
#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include <Learning/Evolution/CoevolutionLearningRule.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>

namespace LightBulb
{
	void AbstractCoevolutionTrainingPlan::fillDefaultLearningRuleOptions(CoevolutionLearningRuleOptions& options) const
	{
		AbstractEvolutionTrainingPlan::fillDefaultLearningRuleOptions(options);
	}

	void AbstractCoevolutionTrainingPlan::fillDefaultEvolutionLearningRule1Options(EvolutionLearningRuleOptions& options) const
	{
		options.environment = environment.get();
	}

	void AbstractCoevolutionTrainingPlan::fillDefaultEvolutionLearningRule2Options(EvolutionLearningRuleOptions& options) const
	{
		options.environment = parasiteEnvironment.get();
	}

	void AbstractCoevolutionTrainingPlan::initializeStart()
	{
		parasiteEnvironment.reset(createParasiteEnvironment());
		AbstractEvolutionTrainingPlan::initializeStart();
	}

	AbstractEvolutionEnvironment& AbstractCoevolutionTrainingPlan::getParasiteEnvironment()
	{
		return *parasiteEnvironment.get();
	}

}