// Includes
#include "TrainingPlans/Preferences/AbstractSupervisedLearningRulePreferenceGroup.hpp"
#include "SimpleGradientDescentPreferenceGroup.hpp"
#include "DoublePreference.hpp"
#include "IntegerPreference.hpp"
#include "BooleanPreference.hpp"

#define PREFERENCE_TOTAL_ERROR_GOAL "Total error goal"
#define PREFERENCE_MIN_RANDOM "Min random weight value"
#define PREFERENCE_MAX_RANDOM "Max random weight value"
#define PREFERENCE_MIN_ITERATIONS_PER_TRY "Min iterations per try"
#define PREFERENCE_MAX_TOTAL_ERROR "Max total error value"
#define PREFERENCE_OFFLINE_LEARNING "Offline learning"
#define PREFERENCE_CHANGE_WEIGHTS_BEFORE_LEARNING "Change weights before learning"
#define PREFERENCE_CLIP_ERROR "Clip error"

namespace LightBulb
{
	AbstractSupervisedLearningRulePreferenceGroup::AbstractSupervisedLearningRulePreferenceGroup(std::string name)
		:PreferenceGroup(name)
	{
		AbstractSupervisedLearningRuleOptions options;
		initialize(options);
	}

	AbstractSupervisedLearningRulePreferenceGroup::AbstractSupervisedLearningRulePreferenceGroup(AbstractSupervisedLearningRuleOptions& options, std::string name)
		:PreferenceGroup(name)
	{
		initialize(options);
	}

	void AbstractSupervisedLearningRulePreferenceGroup::initialize(AbstractSupervisedLearningRuleOptions& options)
	{
		preferences.clear();
		addPreference(new DoublePreference(PREFERENCE_TOTAL_ERROR_GOAL, options.totalErrorGoal, 0.0001, 2));
		addPreference(new DoublePreference(PREFERENCE_MIN_RANDOM, options.minRandomWeightValue, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_MAX_RANDOM, options.maxRandomWeightValue, 0, 1));
		addPreference(new IntegerPreference(PREFERENCE_MIN_ITERATIONS_PER_TRY, options.minIterationsPerTry, 0.0001, 2));
		addPreference(new DoublePreference(PREFERENCE_MAX_TOTAL_ERROR, options.maxTotalErrorValue, 0, 1));
		addPreference(new BooleanPreference(PREFERENCE_OFFLINE_LEARNING, options.offlineLearning));
		addPreference(new BooleanPreference(PREFERENCE_CHANGE_WEIGHTS_BEFORE_LEARNING, options.changeWeightsBeforeLearning));
		addPreference(new BooleanPreference(PREFERENCE_CLIP_ERROR, options.clipError));
	}
	
	void AbstractSupervisedLearningRulePreferenceGroup::fillOptions(AbstractSupervisedLearningRuleOptions& options)
	{
		options.totalErrorGoal = getDoublePreference(PREFERENCE_TOTAL_ERROR_GOAL);
		options.minRandomWeightValue = getDoublePreference(PREFERENCE_MIN_RANDOM);
		options.maxRandomWeightValue = getDoublePreference(PREFERENCE_MAX_RANDOM);
		options.minIterationsPerTry = getIntegerPreference(PREFERENCE_MIN_ITERATIONS_PER_TRY);
		options.maxTotalErrorValue = getDoublePreference(PREFERENCE_MAX_TOTAL_ERROR);
		options.offlineLearning = getBooleanPreference(PREFERENCE_OFFLINE_LEARNING);
		options.changeWeightsBeforeLearning = getBooleanPreference(PREFERENCE_CHANGE_WEIGHTS_BEFORE_LEARNING);
		options.clipError = getBooleanPreference(PREFERENCE_CLIP_ERROR);
	}
}
