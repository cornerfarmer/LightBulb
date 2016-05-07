// Includes
#include "TrainingPlans/IntegerPreference.hpp"


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

AbstractPreference* IntegerPreference::getCopy()
{
	return new IntegerPreference(*this);
}
