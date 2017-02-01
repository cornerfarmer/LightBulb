// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Reinforcement/PolicyGradientLearningRulePreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentAlgorithms/RMSPropLearningRatePreferenceGroup.hpp"

namespace LightBulb
{
	#define PREFERENCE_EPISODE_SIZE "Episode size"
	#define PREFERENCE_RATING_INTERVAL "Rating interval"
	#define PREFERENCE_VALUE_FUNCTION_BASE "Enable value function as base"
	#define PREFERENCE_VALUE_FUNCTION_BASE_RMS_PROP "Value function RMSProp"

	PolicyGradientLearningRulePreferenceGroup::PolicyGradientLearningRulePreferenceGroup(const std::string& name)
		:AbstractReinforcementLearningRulePreferenceGroup(name)
	{
		PolicyGradientLearningRuleOptions options;
		initialize(options);
	}

	PolicyGradientLearningRulePreferenceGroup::PolicyGradientLearningRulePreferenceGroup(const PolicyGradientLearningRuleOptions& options, const std::string& name)
		:AbstractReinforcementLearningRulePreferenceGroup(options, name)
	{
		initialize(options);
	}

	void PolicyGradientLearningRulePreferenceGroup::initialize(const PolicyGradientLearningRuleOptions& options)
	{
		AbstractReinforcementLearningRulePreferenceGroup::initialize(options);

		addPreference(new IntegerPreference(PREFERENCE_EPISODE_SIZE, options.episodeSize, 1, 100));
		addPreference(new IntegerPreference(PREFERENCE_RATING_INTERVAL, options.ratingInterval, 1, 100));

		addPreference(new RMSPropLearningRatePreferenceGroup(options.rmsPropLearningRateOptions));
		addPreference(new BooleanPreference(PREFERENCE_VALUE_FUNCTION_BASE, options.valueFunctionAsBase));
		addPreference(new RMSPropLearningRatePreferenceGroup(options.valueRmsPropLearningRateOptions, PREFERENCE_VALUE_FUNCTION_BASE_RMS_PROP));
	}
	
	PolicyGradientLearningRuleOptions PolicyGradientLearningRulePreferenceGroup::create() const
	{
		PolicyGradientLearningRuleOptions options;
		fillOptions(options);

		options.episodeSize = getIntegerPreference(PREFERENCE_EPISODE_SIZE);
		options.ratingInterval = getIntegerPreference(PREFERENCE_RATING_INTERVAL);
		options.valueFunctionAsBase = getBooleanPreference(PREFERENCE_VALUE_FUNCTION_BASE);

		options.rmsPropLearningRateOptions = createFromGroup<RMSPropLearningRateOptions, RMSPropLearningRatePreferenceGroup>();
		options.valueRmsPropLearningRateOptions = createFromGroup<RMSPropLearningRateOptions, RMSPropLearningRatePreferenceGroup>(PREFERENCE_VALUE_FUNCTION_BASE_RMS_PROP);
		return options;
	}

	AbstractCloneable* PolicyGradientLearningRulePreferenceGroup::clone() const
	{
		return new PolicyGradientLearningRulePreferenceGroup(*this);
	}
}
