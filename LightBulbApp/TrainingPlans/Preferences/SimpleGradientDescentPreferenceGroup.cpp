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
		SimpleGradientDescentOptions options;
		initialize(options);
	}

	SimpleGradientDescentPreferenceGroup::SimpleGradientDescentPreferenceGroup(SimpleGradientDescentOptions& options, std::string name)
		:PreferenceGroup(name)
	{
		initialize(options);
	}

	void SimpleGradientDescentPreferenceGroup::initialize(SimpleGradientDescentOptions& options)
	{
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE, options.learningRate, 0.0001, 2));
		addPreference(new DoublePreference(PREFERENCE_MOMENTUM, options.momentum, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_WEIGHT_DECAY, options.weightDecayFac, 0, 1));
	}

	SimpleGradientDescentOptions SimpleGradientDescentPreferenceGroup::create()
	{
		SimpleGradientDescentOptions options;
		options.learningRate = getDoublePreference(PREFERENCE_LEARNINGRATE);
		options.momentum = getDoublePreference(PREFERENCE_MOMENTUM);
		options.weightDecayFac = getDoublePreference(PREFERENCE_WEIGHT_DECAY);
		return options;
	}

	AbstractPreferenceElement* SimpleGradientDescentPreferenceGroup::getCopy()
	{
		return new SimpleGradientDescentPreferenceGroup(*this);
	}
}
