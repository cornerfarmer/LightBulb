﻿// Includes
#include "TrainingPlans/AbstractPreference.hpp"


AbstractPreference::AbstractPreference(std::string name_)
{
	name = name_;
}

std::string AbstractPreference::getName()
{
	return name;
}

std::string AbstractPreference::toString()
{
	return name + " -> " + getValueAsString() + "\n";
}
