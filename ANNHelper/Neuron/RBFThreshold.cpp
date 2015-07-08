#include "Neuron\RBFThreshold.hpp"

RBFThreshold::RBFThreshold(std::vector<float> &centerVector_, float width_)
{
	centerVector = centerVector_;
	width = width_;
}

void RBFThreshold::setCenterVector(std::vector<float> &newCenterVector)
{
	centerVector = newCenterVector;
}

std::vector<float>* RBFThreshold::getCenterVector()
{
	return &centerVector;
}

float RBFThreshold::getWidth()
{
	return width;
}

void RBFThreshold::setWidth(float newWidth)
{
	width = newWidth;
}

AbstractThreshold* RBFThreshold::getCopy()
{
	return new RBFThreshold(*this);
}

