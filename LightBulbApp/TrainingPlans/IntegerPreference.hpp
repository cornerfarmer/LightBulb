#pragma once

#ifndef _INTEGERPREFERENCE_H_
#define _INTEGERPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

// Forward declarations

class IntegerPreference : public AbstractVariablePreference<int>
{
protected:
	int min;
	int max;
public:
	IntegerPreference(std::string name, int defaultValue, int min_, int max_);

	int getMin();
	int getMax();
	AbstractPreference* getCopy();
};

#endif
