// Includes
#include "TrainingPlans/Preferences/SimpleGradientDescentPreferenceGroup.hpp"
#include "DoublePreference.hpp"

namespace LightBulb
{
	#define PREFERENCE_LEARNINGRATE "Learning rate"
	#define PREFERENCE_MOMENTUM "Momentum"
	#define PREFERENCE_WEIGHT_DECAY "Weight decay"

	SimpleGradientDescentPreferenceGroup::SimpleGradientDescentPreferenceGroup(std::string name)
		:PreferenceGroup(name)
	{
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE, 0.1, 0.0001, 2));
		addPreference(new DoublePreference(PREFERENCE_MOMENTUM, 0, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_WEIGHT_DECAY, 0, 0, 1));
	}

	SimpleGradientDescentOptions SimpleGradientDescentPreferenceGroup::createOptions()
	{
		SimpleGradientDescentOptions options;
		options.learningRate = getDoublePreference(PREFERENCE_LEARNINGRATE);
		options.momentum = getDoublePreference(PREFERENCE_MOMENTUM);
		options.weightDecayFac = getDoublePreference(PREFERENCE_WEIGHT_DECAY);
		return options;
	}
}
