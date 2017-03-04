// Includes
#include "LightBulbApp/TrainingPlans/AbstractReinforcementTrainingPlan.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementIndividual.hpp"

namespace LightBulb
{
	void AbstractReinforcementTrainingPlan::fillDefaultLearningRuleOptions(AbstractReinforcementLearningRuleOptions& options) const
	{
		AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
		options.environment = environment.get();
		options.individual = individual.get();
	}

	AbstractReinforcementTrainingPlan::~AbstractReinforcementTrainingPlan() = default;

	AbstractReinforcementTrainingPlan::AbstractReinforcementTrainingPlan()
	{
		environment = nullptr;
		individual = nullptr;
	}

	void AbstractReinforcementTrainingPlan::initializeStart()
	{
		environment.reset(createEnvironment());
		individual.reset(createIndividual());
	}

	AbstractReinforcementEnvironment& AbstractReinforcementTrainingPlan::getEnvironment()
	{
		return *environment.get();
	}

	AbstractReinforcementIndividual& AbstractReinforcementTrainingPlan::getIndividual()
	{
		return *individual.get();
	}
}
