// Includes
#include "TrainingPlans/Preferences/IntegerPreference.hpp"

namespace LightBulb
{
	IntegerPreference::IntegerPreference(std::string name, int defaultValue, int min_, int max_)
		:AbstractVariablePreference(name, defaultValue)
	{
		min = min_;
		max = max_;
	}

	int IntegerPreference::getMin()
	{
		return min;
	}

	int IntegerPreference::getMax()
	{
		return max;
	}

	AbstractPreferenceElement* IntegerPreference::getCopy()
	{
		return new IntegerPreference(*this);
	}

	std::string IntegerPreference::getValueAsString()
	{
		return std::to_string(value);
	}
}