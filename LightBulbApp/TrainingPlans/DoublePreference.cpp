// Includes
#include "TrainingPlans/DoublePreference.hpp"



DoublePreference::DoublePreference(std::string name, double defaultValue, double min_, double max_)
	:AbstractVariablePreference(name, defaultValue)
{
	min = min_;
	max = max_;
}

double DoublePreference::getMin()
{
	return min;
}

double DoublePreference::getMax()
{
	return max;
}

AbstractPreference* DoublePreference::getCopy()
{
	return new DoublePreference(*this);
}

std::string DoublePreference::getValueAsString()
{
	return std::to_string(value);
}