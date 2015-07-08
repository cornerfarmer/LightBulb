#pragma once

#ifndef _STANDARDTHRESHOLD_H_
#define _STANDARDTHRESHOLD_H_

// Includes
#include "Neuron\AbstractThreshold.hpp"

// A StandardThreshold just consists of one float value
class StandardThreshold : public AbstractThreshold
{
private:
	float value;
public:
	StandardThreshold(float value_);
	float getThreshold();
	void setThreshold(float threshold);
	AbstractThreshold* getCopy();
};

#endif