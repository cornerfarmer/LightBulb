#pragma once

#ifndef _CHANGEABLEPOINTER_H_
#define _CHANGEABLEPOINTER_H_

// Includes
#include "Diagnostic/AbstractChangeableParameter.hpp"

//Library includes
#include <stdexcept>
#include <vector>
#include <utility>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

// A class which describes any kind of number which should be changed
// T: type of the number, O: Class which contains the setter of the parameter (only needed if a function pointer is used!)
template<typename T, typename O = AbstractChangeableParameter>
class ChangeablePointer : public AbstractChangeableParameter
{
private:
	// 1. Way: A simple pointer to the pointer, which is used to modify it
	T** pointerToPointer;
	// 2. Way: A pointer to a setter which should be used to modify the pointer
	void (O::*pointerToFunction)(T*);
	// The object which contains the pointer
	O* object;
	//
	std::vector<std::pair<std::string, T*>> possibleValues;
	//
	int currentIndex;
	std::string name;

	// This method sets the value from the internal variable to the chosen variable (per value- or function pointer)
	void setValue()
	{
		// Decide whether to directly modify the parameter or to use a setter
		if (pointerToPointer)
			*pointerToPointer = possibleValues[currentIndex].second;
		else
			(object->*pointerToFunction)(possibleValues[currentIndex].second);
	}
public:
	// Use this constructor if you want to modify the parameter with a simple pointer
	ChangeablePointer(T** pointerToPointer_, std::vector<std::pair<std::string, T*>>& possibleValues_, std::string name_ = "")
	{
		// Make sure all given parameters are valid

		pointerToFunction = NULL;
		object = NULL;
		pointerToPointer = pointerToPointer_;
		name = name_;
		possibleValues = possibleValues_;
	}

	// Use this constructor if you want to modify the parameter with a function pointer to the corresponding setter and the object which contains the parameter
	// Second template type needed!
	ChangeablePointer(O* object_, void (O::*pointerToFunction_)(T*), std::vector<std::pair<std::string, T*>>& possibleValues_, std::string name_ = "")
	{
		// Make sure all given parameters are valid
		if (!pointerToFunction_)
			throw std::invalid_argument("PointerToFunction cannot be NULL!");
		if (!object_)
			throw std::invalid_argument("Object cannot be NULL!");

		pointerToFunction = pointerToFunction_;
		object = object_;
		pointerToPointer = NULL;
		possibleValues = possibleValues_;
		name = name_;
	}

	// Increases the value by adding the interval
	bool switchToNextValue()
	{
		// Decide whether we have already reached the end
		if (currentIndex + 1 >= possibleValues.size())
		{
			// Start from the beginning again
			resetToStart();
			setValue();
			return true;
		}
		else
		{
			//
			currentIndex++;
			setValue();
			return false;
		}
	}

	void resetToStart()
	{
		//
		currentIndex = 0;
		setValue();
	}

	std::string printCurrentValue()
	{
		std::ostringstream strs;
		strs << std::fixed << std::setprecision(5) << possibleValues[currentIndex].first;
		return name + ": " + strs.str();
	}
};

#endif
