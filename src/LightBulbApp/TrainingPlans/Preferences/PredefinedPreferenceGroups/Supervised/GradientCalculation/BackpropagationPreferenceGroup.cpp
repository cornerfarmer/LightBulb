// Includes
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientCalculation/BackpropagationPreferenceGroup.hpp"
#include "TrainingPlans/Preferences/DoublePreference.hpp"


namespace LightBulb
{
	#define PREFERENCE_FLATSPOT_ELIMINATION_FAC "Flatspot elimination factor"

	BackpropagationPreferenceGroup::BackpropagationPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		addPreference(new DoublePreference(PREFERENCE_FLATSPOT_ELIMINATION_FAC, 0, 0, 1));
	}

	Backpropagation* BackpropagationPreferenceGroup::create() const
	{
		Backpropagation options;
		double flatSpotEliminationFac = getDoublePreference(PREFERENCE_FLATSPOT_ELIMINATION_FAC);
		return new Backpropagation(flatSpotEliminationFac);
	}

	AbstractCloneable* BackpropagationPreferenceGroup::clone() const
	{
		return new BackpropagationPreferenceGroup(*this);
	}
}
