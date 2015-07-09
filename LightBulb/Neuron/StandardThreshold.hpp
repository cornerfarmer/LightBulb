#pragma once

#ifndef _STANDARDTHRESHOLD_H_
#define _STANDARDTHRESHOLD_H_

// Includes
#include "Neuron\AbstractThreshold.hpp"

// A StandardThreshold just consists of one double value
class StandardThreshold : public AbstractThreshold
{
private:
	double value;
public:
	StandardThreshold(double value_);
	double getThreshold();
	void setThreshold(double threshold);
	AbstractThreshold* getCopy();
};

#endif