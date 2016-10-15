// Includes
#include "TrainingPlans/Preferences/BackpropagationPreferenceGroup.hpp"
#include "DoublePreference.hpp"

namespace LightBulb
{
	#define PREFERENCE_FLATSPOT_ELIMINATION_FAC "Flatspot elimination factor"

	BackpropagationPreferenceGroup::BackpropagationPreferenceGroup(std::string name)
		:PreferenceGroup(name)
	{
		addPreference(new DoublePreference(PREFERENCE_FLATSPOT_ELIMINATION_FAC, 0, 0, 1));
	}

	Backpropagation* BackpropagationPreferenceGroup::create()
	{
		Backpropagation options;
		double flatSpotEliminationFac = getDoublePreference(PREFERENCE_FLATSPOT_ELIMINATION_FAC);
		return new Backpropagation(flatSpotEliminationFac);
	}

	AbstractPreferenceElement* BackpropagationPreferenceGroup::getCopy()
	{
		return new BackpropagationPreferenceGroup(*this);
	}
}
