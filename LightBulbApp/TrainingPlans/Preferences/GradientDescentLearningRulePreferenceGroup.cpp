// Includes
#include "TrainingPlans/Preferences/GradientDescentLearningRulePreferenceGroup.hpp"
#include "SimpleGradientDescentPreferenceGroup.hpp"

namespace LightBulb
{

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(std::string name)
		:PreferenceGroup(name)
	{
		addPreference(new SimpleGradientDescentPreferenceGroup());
	}

	GradientDescentLearningRuleOptions GradientDescentLearningRulePreferenceGroup::createOptions()
	{
		GradientDescentLearningRuleOptions options;
		SimpleGradientDescentOptions gradientDescentOptions = createOptionsFromGroup<SimpleGradientDescentOptions, SimpleGradientDescentPreferenceGroup>();
		options.gradientDescentAlgorithm = new SimpleGradientDescent();
		return options;
	}
}
