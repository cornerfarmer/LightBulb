#include "Neuron\StandardThreshold.hpp"

StandardThreshold::StandardThreshold(float value_)
{
	value = value_;
}

float StandardThreshold::getThreshold()
{
	return value;
}

void StandardThreshold::setThreshold(float threshold)
{
	value = threshold;
}

AbstractThreshold* StandardThreshold::getCopy()
{
	return new StandardThreshold(*this);
}