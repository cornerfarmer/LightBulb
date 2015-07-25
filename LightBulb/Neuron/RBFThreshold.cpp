// Includes
#include "Neuron\RBFThreshold.hpp"

RBFThreshold::RBFThreshold(double width_)
{
	width = width_;
}

double RBFThreshold::getWidth()
{
	return width;
}

void RBFThreshold::setWidth(double newWidth)
{
	width = newWidth;
}

AbstractThreshold* RBFThreshold::getCopy()
{
	return new RBFThreshold(*this);
}

