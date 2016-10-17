// Includes
#include "TrainingPlans/Preferences/BooleanPreference.hpp"

namespace LightBulb
{
	BooleanPreference::BooleanPreference(const std::string& name, bool defaultValue)
		:AbstractVariablePreference(name, defaultValue)
	{
	}

	AbstractPreferenceElement* BooleanPreference::getCopy() const
	{
		return new BooleanPreference(*this);
	}

	std::string BooleanPreference::getValueAsString() const
	{
		return std::to_string(value);
	}
}