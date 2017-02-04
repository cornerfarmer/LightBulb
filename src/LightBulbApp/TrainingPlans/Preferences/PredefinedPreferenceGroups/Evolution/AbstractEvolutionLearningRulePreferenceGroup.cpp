// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/AbstractEvolutionLearningRulePreferenceGroup.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionLearningRule.hpp"

namespace LightBulb
{
	AbstractEvolutionLearningRulePreferenceGroup::AbstractEvolutionLearningRulePreferenceGroup(const std::string& name)
		:AbstractLearningRulePreferenceGroup(name)
	{
		AbstractEvolutionLearningRuleOptions options;
		initialize(options);
	}

	AbstractEvolutionLearningRulePreferenceGroup::AbstractEvolutionLearningRulePreferenceGroup(const AbstractEvolutionLearningRuleOptions& options, const std::string& name)
		:AbstractLearningRulePreferenceGroup(options, name)
	{
		initialize(options);
	}

	void AbstractEvolutionLearningRulePreferenceGroup::initialize(const AbstractEvolutionLearningRuleOptions& options)
	{
		AbstractLearningRulePreferenceGroup::initialize(options);
	}
	
	void AbstractEvolutionLearningRulePreferenceGroup::fillOptions(AbstractEvolutionLearningRuleOptions& options) const
	{
		AbstractLearningRulePreferenceGroup::fillOptions(options);
	}
}
