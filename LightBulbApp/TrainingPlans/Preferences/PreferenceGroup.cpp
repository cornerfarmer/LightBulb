// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"

namespace LightBulb
{
	PreferenceGroup::PreferenceGroup(std::string name_)
	{
		name = name_;
	}

	std::string PreferenceGroup::getName()
	{
		return name;
	}

	std::string PreferenceGroup::toString()
	{
		std::string text = name + ":\n";
		for (auto preference = preferences.begin(); preference !=preferences.end(); preference++)
		{
			text += "    - " + (*preference)->toString();
		}
		return text;
	}


	PreferenceGroup* PreferenceGroup::getCopy()
	{
		PreferenceGroup* preferenceGroup = new PreferenceGroup(name);
		
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			preferenceGroup->addPreference((*preference)->getCopy());
		}
		
		return preferenceGroup;
	}


	void PreferenceGroup::addPreference(AbstractPreference* preference)
	{
		preferences.push_back(std::unique_ptr<AbstractPreference>(preference));
	}

	AbstractPreference* PreferenceGroup::getPreference(std::string name)
	{
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			if ((*preference)->getName() == name)
				return preference->get();
		}
		return NULL;
	}

	std::vector<std::unique_ptr<AbstractPreference>>& PreferenceGroup::getPreferences()
	{
		return preferences;
	}
}
