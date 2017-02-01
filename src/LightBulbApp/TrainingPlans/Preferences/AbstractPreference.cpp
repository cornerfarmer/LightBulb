// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/AbstractPreference.hpp"

namespace LightBulb
{
	AbstractPreference::AbstractPreference(std::string name_)
	{
		name = name_;
	}

	const std::string& AbstractPreference::getName() const
	{
		return name;
	}

	void AbstractPreference::setName(std::string newName)
	{
		name = newName;
	}

	std::string AbstractPreference::toString(std::string offset) const
	{
		return name + " -> " + getValueAsString() + "\n";
	}
}