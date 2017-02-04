// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentAlgorithms/SimpleGradientDescentPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"

namespace LightBulb
{
	#define PREFERENCE_LEARNINGRATE "Learning rate"
	#define PREFERENCE_MOMENTUM "Momentum"
	#define PREFERENCE_WEIGHT_DECAY "Weight decay"

	SimpleGradientDescentPreferenceGroup::SimpleGradientDescentPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		SimpleGradientDescentOptions options;
		initialize(options);
	}

	SimpleGradientDescentPreferenceGroup::SimpleGradientDescentPreferenceGroup(const SimpleGradientDescentOptions& options, const std::string& name)
		:PreferenceGroup(name)
	{
		initialize(options);
	}

	void SimpleGradientDescentPreferenceGroup::initialize(const SimpleGradientDescentOptions& options)
	{
		addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE, options.learningRate, 0.0001, 2));
		addPreference(new DoublePreference(PREFERENCE_MOMENTUM, options.momentum, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_WEIGHT_DECAY, options.weightDecayFac, 0, 1));
	}

	SimpleGradientDescentOptions SimpleGradientDescentPreferenceGroup::create() const
	{
		SimpleGradientDescentOptions options;
		options.learningRate = getDoublePreference(PREFERENCE_LEARNINGRATE);
		options.momentum = getDoublePreference(PREFERENCE_MOMENTUM);
		options.weightDecayFac = getDoublePreference(PREFERENCE_WEIGHT_DECAY);
		return options;
	}

	AbstractCloneable* SimpleGradientDescentPreferenceGroup::clone() const
	{
		return new SimpleGradientDescentPreferenceGroup(*this);
	}
}
