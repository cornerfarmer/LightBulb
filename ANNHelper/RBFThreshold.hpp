#pragma once

#ifndef _RBFTHRESHOLD_H_
#define _RBFTHRESHOLD_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractThreshold.hpp"

// A StandardThreshold just consists of one float value
class RBFThreshold : public AbstractThreshold
{
private:
	// The center of the RBF-Neuron
	std::vector<float> centerVector;
	// The width of the RBF-Neuron
	float width;
public:
	RBFThreshold(std::vector<float> &centerVector_, float width_);
	void setCenterVector(std::vector<float> &newCenterVector);
	std::vector<float>* getCenterVector();
	float getWidth();
	void setWidth(float newWidth);
	AbstractThreshold* getCopy();
};

#endif