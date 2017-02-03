// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Reinforcement/AbstractReinforcementLearningRulePreferenceGroup.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"

namespace LightBulb
{
	AbstractReinforcementLearningRulePreferenceGroup::AbstractReinforcementLearningRulePreferenceGroup(const std::string& name)
		:AbstractLearningRulePreferenceGroup(name)
	{
		AbstractReinforcementLearningRuleOptions options;
		initialize(options);
	}

	AbstractReinforcementLearningRulePreferenceGroup::AbstractReinforcementLearningRulePreferenceGroup(const AbstractReinforcementLearningRuleOptions& options, const std::string& name)
		:AbstractLearningRulePreferenceGroup(options, name)
	{
		initialize(options);
	}

	void AbstractReinforcementLearningRulePreferenceGroup::initialize(const AbstractReinforcementLearningRuleOptions& options)
	{
		AbstractLearningRulePreferenceGroup::initialize(options);
	}
	
	void AbstractReinforcementLearningRulePreferenceGroup::fillOptions(AbstractReinforcementLearningRuleOptions& options) const
	{
		AbstractLearningRulePreferenceGroup::fillOptions(options);
	}
}
