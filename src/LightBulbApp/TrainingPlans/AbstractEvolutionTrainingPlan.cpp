// Includes
#include "LightBulbApp/TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include <LightBulb/Learning/Evolution/AbstractEvolutionLearningRule.hpp>

namespace LightBulb
{
	void AbstractEvolutionTrainingPlan::fillDefaultLearningRuleOptions(AbstractEvolutionLearningRuleOptions& options) const
	{
		AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
		options.environment = environment.get();
	}

	AbstractEvolutionTrainingPlan::AbstractEvolutionTrainingPlan()
	{
		environment = nullptr;
	}

	void AbstractEvolutionTrainingPlan::initializeStart()
	{
		environment.reset(createEnvironment());
	}

	AbstractEvolutionEnvironment& AbstractEvolutionTrainingPlan::getEnvironment()
	{
		return *environment.get();
	}
}