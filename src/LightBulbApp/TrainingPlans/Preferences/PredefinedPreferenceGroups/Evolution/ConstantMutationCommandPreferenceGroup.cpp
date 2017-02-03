// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/ConstantMutationCommandPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulb/Learning/Evolution/ConstantMutationCommand.hpp"
#include "LightBulb/Learning/Evolution/StochasticUniversalSamplingSelector.hpp"
#include "LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"

namespace LightBulb
{
	#define PREFERENCE_INDIVIDUAL_PERCENTAGE "Individual percentage"
	#define PREFERENCE_MUTATION_SPEED "Mutation speed"

	ConstantMutationCommandPreferenceGroup::ConstantMutationCommandPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		addPreference(new DoublePreference(PREFERENCE_INDIVIDUAL_PERCENTAGE, 1.8, 0, 3));
		addPreference(new DoublePreference(PREFERENCE_MUTATION_SPEED, 1.6, 0, 2));
	}

	ConstantMutationCommand* ConstantMutationCommandPreferenceGroup::create() const
	{
		double individualPercentage = getDoublePreference(PREFERENCE_INDIVIDUAL_PERCENTAGE);
		double mutationSpeed = getDoublePreference(PREFERENCE_MUTATION_SPEED);
		return new ConstantMutationCommand(new MutationAlgorithm(mutationSpeed), new StochasticUniversalSamplingSelector(), individualPercentage);
	}

	AbstractCloneable* ConstantMutationCommandPreferenceGroup::clone() const
	{
		return new ConstantMutationCommandPreferenceGroup(*this);
	}
}
