// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientCalculation/BackpropagationPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"


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
