#pragma once

#ifndef _DOUBLEPREFERENCE_H_
#define _DOUBLEPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

// Forward declarations

class DoublePreference : public AbstractVariablePreference<double>
{
protected:
	double min;
	double max;
public:
	DoublePreference(std::string name, double defaultValue, double min_, double max_);

	double getMin();
	double getMax();
	AbstractPreference* getCopy();
};

#endif
