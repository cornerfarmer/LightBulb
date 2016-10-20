// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IntegerPreference.hpp"
#include "DoublePreference.hpp"
#include "BooleanPreference.hpp"
#include "ChoicePreference.hpp"

namespace LightBulb
{
	PreferenceGroup::PreferenceGroup(const std::string& name_)
	{
		name = name_;
	}

	PreferenceGroup::PreferenceGroup(const PreferenceGroup& other)
	{
		name = other.name;
		preferences.clear();
		for (auto preference = other.preferences.begin(); preference != other.preferences.end(); preference++)
		{
			addPreference((*preference)->getCopy());
		}
	}

	const std::string& PreferenceGroup::getName() const
	{
		return name;
	}

	std::string PreferenceGroup::toString() const
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

	AbstractPreferenceElement* PreferenceGroup::getCopy() const
	{
		return new PreferenceGroup(*this);
	}

	const AbstractPreference* PreferenceGroup::getPreference(const std::string& preferenceName) const
	{
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			if (dynamic_cast<AbstractPreference*>(preference->get()) && (*preference)->getName() == preferenceName)
				return dynamic_cast<AbstractPreference*>(preference->get());
		}
		return nullptr;
	}

	PreferenceGroup* PreferenceGroup::getPreferenceGroup(const std::string& preferenceGroupName) const
	{
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			if (dynamic_cast<PreferenceGroup*>(preference->get()) && (*preference)->getName() == preferenceGroupName)
				return dynamic_cast<PreferenceGroup*>(preference->get());
		}
		return nullptr;
	}

	double PreferenceGroup::getDoublePreference(const std::string& preferenceName) const
	{
		const DoublePreference* doublePreference = dynamic_cast<const DoublePreference*>(getPreference(preferenceName));
		if (doublePreference)
			return doublePreference->getValue();
		else
			return 0;
	}


	int PreferenceGroup::getIntegerPreference(const std::string& preferenceName) const
	{
		const IntegerPreference* integerPreference = dynamic_cast<const IntegerPreference*>(getPreference(preferenceName));
		if (integerPreference)
			return integerPreference->getValue();
		else
			return 0;
	}

	bool PreferenceGroup::getBooleanPreference(const std::string& preferenceName) const
	{
		const BooleanPreference* booleanPreference = dynamic_cast<const BooleanPreference*>(getPreference(preferenceName));
		if (booleanPreference)
			return booleanPreference->getValue();
		else
			return false;
	}

	std::string PreferenceGroup::getChoicePreference(const std::string& preferenceName) const
	{
		const ChoicePreference* choicePreference = dynamic_cast<const ChoicePreference*>(getPreference(preferenceName));
		if (choicePreference)
			return choicePreference->getValue();
		else
			return false;
	}

	const std::vector<std::unique_ptr<AbstractPreferenceElement>>& PreferenceGroup::getPreferenceElements() const
	{
		return preferences;
	}

}
