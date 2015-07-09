#include "Neuron\RBFThreshold.hpp"

RBFThreshold::RBFThreshold(std::vector<double> &centerVector_, double width_)
{
	centerVector = centerVector_;
	width = width_;
}

void RBFThreshold::setCenterVector(std::vector<double> &newCenterVector)
{
	centerVector = newCenterVector;
}

std::vector<double>* RBFThreshold::getCenterVector()
{
	return &centerVector;
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

