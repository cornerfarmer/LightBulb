#pragma once

#ifndef _CHANGEABLENUMBER_H_
#define _CHANGEABLENUMBER_H_

// Includes
#include "Diagnostic/AbstractChangeableParameter.hpp"

//Library includes
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

// A class which describes any kind of number which should be changed
// T: type of the number, O: Class which contains the setter of the parameter (only needed if a function pointer is used!)
template<typename T, typename O = AbstractChangeableParameter>
class ChangeableNumber : public AbstractChangeableParameter
{
private:
	// 1. Way: A simple pointer to the parameter, which is used to modify it
	T* pointerToValue;
	// 2. Way: A pointer to a setter which should be used to modify the parameter
	void (O::*pointerToFunction)(T);
	// The object which contains the parameter
	O* object;
	// The start value
	T startValue;
	// The change interval (Must be positive)
	T interval;
	// The end value (Must be bigger than startValue
	T endValue;
	// A internal variable to memorize the current value of the parameter
	T value;
	std::string name;

	// This method sets the value from the internal variable to the chosen variable (per value- or function pointer)
	void setValue()
	{
		// Decide whether to directly modify the parameter or to use a setter
		if (pointerToValue)
			*pointerToValue = value;
		else
			(object->*pointerToFunction)(value);
	}
public:
	// Use this constructor if you want to modify the parameter with a simple pointer
	ChangeableNumber(T* pointerToValue_, T startValue_, T interval_, T endValue_, std::string name_ = "")
	{
		// Make sure all given parameters are valid
		if (startValue_ > endValue_)
			throw std::invalid_argument("EndValue has to be greater than startValue!");
		if (interval_ <= 0)
			throw std::invalid_argument("Interval must be positive!");
		if (!pointerToValue_)
			throw std::invalid_argument("PointerToValue cannot be NULL!");

		pointerToFunction = NULL;
		object = NULL;
		pointerToValue = pointerToValue_;
		startValue = startValue_;
		interval = interval_;
		endValue = endValue_;
		name = name_;
	}

	// Use this constructor if you want to modify the parameter with a function pointer to the corresponding setter and the object which contains the parameter
	// Second template type needed!
	ChangeableNumber(O* object_, void (O::*pointerToFunction_)(T), T startValue_, T interval_, T endValue_, std::string name_ = "")
	{
		// Make sure all given parameters are valid
		if (startValue_ > endValue_)
			throw std::invalid_argument("EndValue has to be greater than startValue!");
		if (interval_ <= 0)
			throw std::invalid_argument("Interval must be positive!");
		if (!pointerToFunction_)
			throw std::invalid_argument("PointerToFunction cannot be NULL!");
		if (!object_)
			throw std::invalid_argument("Object cannot be NULL!");

		pointerToFunction = pointerToFunction_;
		object = object_;
		pointerToValue = NULL;
		startValue = startValue_;
		interval = interval_;
		endValue = endValue_;
		name = name_;
	}

	// Increases the value by adding the interval
	bool switchToNextValue()
	{
		// Decide whether we have already reached the end
		if (value + interval > endValue)
		{
			// Start from the beginning again
			resetToStart();
			setValue();
			return true;
		}
		else
		{
			// Add the interval
			value += interval;
			setValue();
			return false;
		}
	}

	void resetToStart()
	{
		// Just set the value to the chosen start value
		value = startValue;
		setValue();
	}

	std::string printCurrentValue()
	{
		std::ostringstream strs;
		strs << std::fixed << std::setprecision(5) << value;
		return name + ": " + strs.str();
	}
};

#endif
