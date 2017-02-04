// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
#include "LightBulb/Learning/Evolution/CoevolutionLearningRule.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"

namespace LightBulb
{
	AbstractCoevolutionTrainingPlan::AbstractCoevolutionTrainingPlan() = default;

	AbstractCoevolutionTrainingPlan::~AbstractCoevolutionTrainingPlan() = default;

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

