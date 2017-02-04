// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/BestSelectionCommandPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulb/Learning/Evolution/BestSelectionCommand.hpp"


namespace LightBulb
{
	#define PREFERENCE_INDIVIDUAL_COUNT "Individual count"

	BestSelectionCommandPreferenceGroup::BestSelectionCommandPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		addPreference(new IntegerPreference(PREFERENCE_INDIVIDUAL_COUNT, 20, 1, 100));
	}

	BestSelectionCommand* BestSelectionCommandPreferenceGroup::create() const
	{
		int flatSpotEliminationFac = getIntegerPreference(PREFERENCE_INDIVIDUAL_COUNT);
		return new BestSelectionCommand(flatSpotEliminationFac);
	}

	AbstractCloneable* BestSelectionCommandPreferenceGroup::clone() const
	{
		return new BestSelectionCommandPreferenceGroup(*this);
	}
}
