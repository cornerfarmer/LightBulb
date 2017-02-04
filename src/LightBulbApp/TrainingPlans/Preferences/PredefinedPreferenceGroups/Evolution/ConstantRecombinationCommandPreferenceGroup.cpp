// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/ConstantRecombinationCommandPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulb/Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "LightBulb/Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/StochasticUniversalSamplingSelector.hpp"

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
