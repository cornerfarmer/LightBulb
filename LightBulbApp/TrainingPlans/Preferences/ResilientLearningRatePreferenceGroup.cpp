// Includes
#include "TrainingPlans/Preferences/ResilientLearningRatePreferenceGroup.hpp"
#include "DoublePreference.hpp"

namespace LightBulb
{
	#define PREFERENCE_LEARNINGRATE_GROW_FAC "Learning rate grow factor"
	#define PREFERENCE_LEARNINGRATE_SHRINK_FAC "Learning rate shrink factor"
	#define PREFERENCE_LEARNINGRATE_RATE_MAX "Maximum learning rate"
	#define PREFERENCE_LEARNINGRATE_RATE_MIN "Minimum learning rate"
	#define PREFERENCE_LEARNINGRATE_START "Starting learning rate"

	ResilientLearningRatePreferenceGroup::ResilientLearningRatePreferenceGroup(std::string name)
		:PreferenceGroup(name)
	{
		ResilientLearningRateOptions options;
		initialize(options);
	}


	ResilientLearningRatePreferenceGroup::ResilientLearningRatePreferenceGroup(ResilientLearningRateOptions& options, std::string name)
		:PreferenceGroup(name)
	{
		initialize(options);
	}

	void ResilientLearningRatePreferenceGroup::initialize(ResilientLearningRateOptions& options)
	{
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE_GROW_FAC, options.learningRateGrowFac, 1, 10));
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE_SHRINK_FAC, options.learningRateShrinkFac, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE_RATE_MAX, options.learningRateMax, 0, 100));
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE_RATE_MIN, options.learningRateMin, 0, 0.1));
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE_START, options.learningRateStart, 0, 1));
	}

	ResilientLearningRateOptions ResilientLearningRatePreferenceGroup::create()
	{
		ResilientLearningRateOptions options;
		options.learningRateGrowFac = getDoublePreference(PREFERENCE_LEARNINGRATE_GROW_FAC);
		options.learningRateShrinkFac = getDoublePreference(PREFERENCE_LEARNINGRATE_SHRINK_FAC);
		options.learningRateMax = getDoublePreference(PREFERENCE_LEARNINGRATE_RATE_MAX);
		options.learningRateMin = getDoublePreference(PREFERENCE_LEARNINGRATE_RATE_MIN);
		options.learningRateStart = getDoublePreference(PREFERENCE_LEARNINGRATE_START);
		return options;
	}

	AbstractPreferenceElement* ResilientLearningRatePreferenceGroup::getCopy()
	{
		return new ResilientLearningRatePreferenceGroup(*this);
	}
}
