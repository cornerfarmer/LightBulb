// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IntegerPreference.hpp"
#include "DoublePreference.hpp"
#include "BooleanPreference.hpp"

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

	void PreferenceGroup::addPreference(AbstractPreferenceElement* preferenceElement)
	{
		preferences.push_back(std::unique_ptr<AbstractPreferenceElement>(preferenceElement));
	}

	AbstractPreferenceElement* PreferenceGroup::getCopy()
	{
		PreferenceGroup* preferenceGroup = new PreferenceGroup(name);
		
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			preferenceGroup->addPreference((*preference)->getCopy());
		}
		
		return preferenceGroup;
	}

	AbstractPreference* PreferenceGroup::getPreference(std::string preferenceName)
	{
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			if (dynamic_cast<AbstractPreference*>(preference->get()) && (*preference)->getName() == preferenceName)
				return dynamic_cast<AbstractPreference*>(preference->get());
		}
		return NULL;
	}

	PreferenceGroup* PreferenceGroup::getPreferenceGroup(std::string preferenceGroupName)
	{
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			if (dynamic_cast<PreferenceGroup*>(preference->get()) && (*preference)->getName() == preferenceGroupName)
				return dynamic_cast<PreferenceGroup*>(preference->get());
		}
		return NULL;
	}

	double PreferenceGroup::getDoublePreference(std::string preferenceName)
	{
		DoublePreference* doublePreference = dynamic_cast<DoublePreference*>(getPreference(preferenceName));
		if (doublePreference)
			return doublePreference->getValue();
		else
			return 0;
	}


	int PreferenceGroup::getIntegerPreference(std::string preferenceName)
	{
		IntegerPreference* integerPreference = dynamic_cast<IntegerPreference*>(getPreference(preferenceName));
		if (integerPreference)
			return integerPreference->getValue();
		else
			return 0;
	}

	bool PreferenceGroup::getBooleanPreference(std::string preferenceName)
	{
		BooleanPreference* booleanPreference = dynamic_cast<BooleanPreference*>(getPreference(preferenceName));
		if (booleanPreference)
			return booleanPreference->getValue();
		else
			return false;
	}

	std::vector<std::unique_ptr<AbstractPreferenceElement>>& PreferenceGroup::getPreferenceElements()
	{
		return preferences;
	}

}
