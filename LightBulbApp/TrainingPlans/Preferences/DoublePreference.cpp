// Includes
#include "TrainingPlans/Preferences/DoublePreference.hpp"

namespace LightBulb
{
	DoublePreference::DoublePreference(const std::string& name, double defaultValue, double min_, double max_)
		:AbstractVariablePreference(name, defaultValue)
	{
		min = min_;
		max = max_;
	}

	double DoublePreference::getMin() const
	{
		return min;
	}

	double DoublePreference::getMax() const
	{
		return max;
	}

	AbstractPreferenceElement* DoublePreference::getCopy() const
	{
		return new DoublePreference(*this);
	}

	std::string DoublePreference::getValueAsString() const
	{
		return std::to_string(value);
	}
}