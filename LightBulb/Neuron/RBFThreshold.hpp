#pragma once

#ifndef _RBFTHRESHOLD_H_
#define _RBFTHRESHOLD_H_

// Library Includes
#include <vector>

// Includes
#include "Neuron/AbstractThreshold.hpp"

// A StandardThreshold just consists of one double value
class RBFThreshold : public AbstractThreshold
{
private:
	// The width of the RBF-Neuron
	double width;
public:
	RBFThreshold(double width_);
	double getWidth();
	void setWidth(double newWidth);
	// Inherited:
	AbstractThreshold* getCopy();
};

#endif