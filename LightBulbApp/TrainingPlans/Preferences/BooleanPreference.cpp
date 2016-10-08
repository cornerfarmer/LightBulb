// Includes
#include "TrainingPlans/Preferences/BooleanPreference.hpp"

namespace LightBulb
{
	BooleanPreference::BooleanPreference(std::string name, bool defaultValue)
		:AbstractVariablePreference(name, defaultValue)
	{
	}

	AbstractPreferenceElement* BooleanPreference::getCopy()
	{
		return new BooleanPreference(*this);
	}

	std::string BooleanPreference::getValueAsString()
	{
		return std::to_string(value);
	}
}