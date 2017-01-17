// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/AbstractSupervisedLearningRulePreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"

#define PREFERENCE_TOTAL_ERROR_GOAL "Total error goal"
#define PREFERENCE_MIN_RANDOM "Min random weight value"
#define PREFERENCE_MAX_RANDOM "Max random weight value"
#define PREFERENCE_MIN_ITERATIONS_PER_TRY "Min iterations per try"
#define PREFERENCE_MAX_TOTAL_ERROR "Max total error value"
#define PREFERENCE_OFFLINE_LEARNING "Offline learning"
#define PREFERENCE_CHANGE_WEIGHTS_BEFORE_LEARNING "Change weights before learning"
#define PREFERENCE_CLIP_ERROR "Clip error"
#define PREFERENCE_TOTAL_ERROR_CALCULATION_INTERVAL "Total error calculation interval"

namespace LightBulb
{
	AbstractSupervisedLearningRulePreferenceGroup::AbstractSupervisedLearningRulePreferenceGroup(const std::string& name)
		:AbstractLearningRulePreferenceGroup(name)
	{
		AbstractSupervisedLearningRuleOptions options;
		initialize(options);
	}

	AbstractSupervisedLearningRulePreferenceGroup::AbstractSupervisedLearningRulePreferenceGroup(const AbstractSupervisedLearningRuleOptions& options, const std::string& name)
		:AbstractLearningRulePreferenceGroup(options, name)
	{
		initialize(options);
	}

	void AbstractSupervisedLearningRulePreferenceGroup::initialize(const AbstractSupervisedLearningRuleOptions& options)
	{
		AbstractLearningRulePreferenceGroup::initialize(options);
		addPreference(new DoublePreference(PREFERENCE_TOTAL_ERROR_GOAL, options.totalErrorGoal, 0.0001, 2));
		addPreference(new IntegerPreference(PREFERENCE_TOTAL_ERROR_CALCULATION_INTERVAL, options.totalErrorCalculationInterval, 1, 30000));
		addPreference(new DoublePreference(PREFERENCE_MIN_RANDOM, options.minRandomWeightValue, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_MAX_RANDOM, options.maxRandomWeightValue, 0, 1));
		addPreference(new IntegerPreference(PREFERENCE_MIN_ITERATIONS_PER_TRY, options.minIterationsPerTry, 0.0001, 2));
		addPreference(new DoublePreference(PREFERENCE_MAX_TOTAL_ERROR, options.maxTotalErrorValue, 0, 1));
		addPreference(new BooleanPreference(PREFERENCE_OFFLINE_LEARNING, options.offlineLearning));
		addPreference(new BooleanPreference(PREFERENCE_CHANGE_WEIGHTS_BEFORE_LEARNING, options.changeWeightsBeforeLearning));
		addPreference(new BooleanPreference(PREFERENCE_CLIP_ERROR, options.clipError));
	}
	
	void AbstractSupervisedLearningRulePreferenceGroup::fillOptions(AbstractSupervisedLearningRuleOptions& options) const
	{
		AbstractLearningRulePreferenceGroup::fillOptions(options);
		options.totalErrorGoal = getDoublePreference(PREFERENCE_TOTAL_ERROR_GOAL);
		options.minRandomWeightValue = getDoublePreference(PREFERENCE_MIN_RANDOM);
		options.maxRandomWeightValue = getDoublePreference(PREFERENCE_MAX_RANDOM);
		options.minIterationsPerTry = getIntegerPreference(PREFERENCE_MIN_ITERATIONS_PER_TRY);
		options.maxTotalErrorValue = getDoublePreference(PREFERENCE_MAX_TOTAL_ERROR);
		options.offlineLearning = getBooleanPreference(PREFERENCE_OFFLINE_LEARNING);
		options.changeWeightsBeforeLearning = getBooleanPreference(PREFERENCE_CHANGE_WEIGHTS_BEFORE_LEARNING);
		options.clipError = getBooleanPreference(PREFERENCE_CLIP_ERROR);
		options.totalErrorCalculationInterval = getIntegerPreference(PREFERENCE_TOTAL_ERROR_CALCULATION_INTERVAL);
	}
}