#include "RBFThreshold.hpp"

RBFThreshold::RBFThreshold(std::vector<float> &centerVector_, float width_)
{
	centerVector = centerVector_;
	width = width_;
}

std::vector<float>* RBFThreshold::getCenterVector()
{
	return NULL;
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

