// Includes
#include "TrainingPlans/BooleanPreference.hpp"

namespace LightBulb
{
	BooleanPreference::BooleanPreference(std::string name, bool defaultValue)
		:AbstractVariablePreference(name, defaultValue)
	{
	}

	AbstractPreference* BooleanPreference::getCopy()
	{
		return new BooleanPreference(*this);
	}

	std::string BooleanPreference::getValueAsString()
	{
		return std::to_string(value);
	}
}