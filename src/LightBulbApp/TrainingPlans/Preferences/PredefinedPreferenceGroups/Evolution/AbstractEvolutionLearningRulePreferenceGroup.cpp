// Includes
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/AbstractEvolutionLearningRulePreferenceGroup.hpp"

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
