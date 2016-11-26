// Includes
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/ConstantRecombinationCommandPreferenceGroup.hpp"
#include "TrainingPlans/Preferences/DoublePreference.hpp"
#include "Learning/Evolution/StochasticUniversalSamplingSelector.hpp"
#include "Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"


namespace LightBulb
{
	#define PREFERENCE_INDIVIDUAL_PERCENTAGE "Individual percentage"

	ConstantRecombinationCommandPreferenceGroup::ConstantRecombinationCommandPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		addPreference(new DoublePreference(PREFERENCE_INDIVIDUAL_PERCENTAGE, 0.3, 0, 3));
	}

	ConstantRecombinationCommand* ConstantRecombinationCommandPreferenceGroup::create() const
	{
		double individualPercentage = getDoublePreference(PREFERENCE_INDIVIDUAL_PERCENTAGE);
		return new ConstantRecombinationCommand(new RecombinationAlgorithm(), new StochasticUniversalSamplingSelector(), individualPercentage);
	}

	AbstractCloneable* ConstantRecombinationCommandPreferenceGroup::clone() const
	{
		return new ConstantRecombinationCommandPreferenceGroup(*this);
	}
}
