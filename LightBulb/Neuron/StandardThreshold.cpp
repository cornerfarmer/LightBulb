#include "Neuron\StandardThreshold.hpp"

StandardThreshold::StandardThreshold(double value_)
{
	value = value_;
}

double StandardThreshold::getThreshold()
{
	return value;
}

void StandardThreshold::setThreshold(double threshold)
{
	value = threshold;
}

AbstractThreshold* StandardThreshold::getCopy()
{
	return new StandardThreshold(*this);
}