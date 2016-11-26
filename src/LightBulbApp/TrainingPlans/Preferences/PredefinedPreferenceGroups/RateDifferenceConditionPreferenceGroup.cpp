// Includes
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/RateDifferenceConditionPreferenceGroup.hpp"
#include "TrainingPlans/Preferences/IntegerPreference.hpp"
#include "TrainingPlans/Preferences/DoublePreference.hpp"


namespace LightBulb
{
	#define PREFERENCE_DIFFERENCE "Difference"
	#define PREFERENCE_ITERATIONS "Iterations"

	RateDifferenceConditionPreferenceGroup::RateDifferenceConditionPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		addPreference(new DoublePreference(PREFERENCE_DIFFERENCE, 0.00001, 0, 1));
		addPreference(new IntegerPreference(PREFERENCE_ITERATIONS, 10, 0, 100));
	}

	RateDifferenceCondition* RateDifferenceConditionPreferenceGroup::create() const
	{
		double difference = getDoublePreference(PREFERENCE_DIFFERENCE);
		int iterations = getIntegerPreference(PREFERENCE_ITERATIONS);
		return new RateDifferenceCondition(difference, iterations);
	}

	AbstractCloneable* RateDifferenceConditionPreferenceGroup::clone() const
	{
		return new RateDifferenceConditionPreferenceGroup(*this);
	}
}
