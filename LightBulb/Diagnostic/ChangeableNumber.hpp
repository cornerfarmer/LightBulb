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

template<typename T, typename O = AbstractChangeableParameter>
class ChangeableNumber : public AbstractChangeableParameter
{
private:
	T* pointerToValue;
	void (O::*pointerToFunction)(T);
	O* object;
	T startValue;
	T interval;
	T endValue;
	T value;
	std::string name;

	void setValue()
	{
		if (pointerToValue)
			*pointerToValue = value;
		else
			(object->*pointerToFunction)(value);
	}
public:
	ChangeableNumber(T* pointerToValue_, T startValue_, T interval_, T endValue_, std::string name_ = "")
	{
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

	ChangeableNumber(O* object_, void (O::*pointerToFunction_)(T), T startValue_, T interval_, T endValue_, std::string name_ = "")
	{
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


	bool switchToNextValue()
	{
		if (value + interval > endValue)
		{
			resetToStart();
			setValue();
			return true;
		}
		else
		{
			value += interval;
			setValue();
			return false;
		}
	}

	void resetToStart()
	{
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
