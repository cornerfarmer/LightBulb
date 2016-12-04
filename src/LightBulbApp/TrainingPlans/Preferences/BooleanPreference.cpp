// Includes
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"

namespace LightBulb
{
	BooleanPreference::BooleanPreference(const std::string& name, bool defaultValue)
		:AbstractVariablePreference(name, defaultValue)
	{
	}

	AbstractCloneable* BooleanPreference::clone() const
	{
		return new BooleanPreference(*this);
	}

	std::string BooleanPreference::getValueAsString() const
	{
		return std::to_string(value);
	}
}