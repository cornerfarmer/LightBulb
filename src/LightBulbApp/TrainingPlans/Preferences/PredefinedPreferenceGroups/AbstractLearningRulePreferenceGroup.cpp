// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/AbstractLearningRulePreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"


#define PREFERENCE_MAX_ITERATIONS_PER_TRY "Max iterations per try"
#define PREFERENCE_MAX_TRIES "Max tries"
#define PREFERENCE_DEBUG_OUTPUT_INTERVAL "Debug output interval"
#define PREFERENCE_DATA_SAVE_INTERVAL "Data save interval"
#define PREFERENCE_SEED "Seed"

namespace LightBulb
{
	AbstractLearningRulePreferenceGroup::AbstractLearningRulePreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		AbstractLearningRuleOptions options;
		initialize(options);
	}

	AbstractLearningRulePreferenceGroup::AbstractLearningRulePreferenceGroup(const AbstractLearningRuleOptions& options, const std::string& name)
		:PreferenceGroup(name)
	{
		initialize(options);
	}

	void AbstractLearningRulePreferenceGroup::initialize(const AbstractLearningRuleOptions& options)
	{
		preferences.clear();
		addPreference(new IntegerPreference(PREFERENCE_MAX_ITERATIONS_PER_TRY , options.maxIterationsPerTry, 1, 1000000));
		addPreference(new IntegerPreference(PREFERENCE_MAX_TRIES, options.maxTries, 1, 1000));
		addPreference(new IntegerPreference(PREFERENCE_DEBUG_OUTPUT_INTERVAL, options.debugOutputInterval, 1, 1000));
		addPreference(new IntegerPreference(PREFERENCE_DATA_SAVE_INTERVAL, options.dataSaveInterval, 1, 1000));
		addPreference(new IntegerPreference(PREFERENCE_SEED, options.seed, -1, 1000000));
	}
	
	void AbstractLearningRulePreferenceGroup::fillOptions(AbstractLearningRuleOptions& options) const
	{
		options.maxIterationsPerTry = getIntegerPreference(PREFERENCE_MAX_ITERATIONS_PER_TRY);
		options.maxTries = getIntegerPreference(PREFERENCE_MAX_TRIES);
		options.debugOutputInterval = getIntegerPreference(PREFERENCE_DEBUG_OUTPUT_INTERVAL);
		options.dataSaveInterval = getIntegerPreference(PREFERENCE_DATA_SAVE_INTERVAL);
		options.seed = getIntegerPreference(PREFERENCE_SEED);
	}
}
