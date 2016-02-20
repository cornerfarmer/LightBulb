#pragma once

#ifndef _ABSTRACTCHANGEABLEPARAMETER_H_
#define _ABSTRACTCHANGEABLEPARAMETER_H_

#include <string>

// Describes any parameter which should be changed while analyzing a learning rule
class AbstractChangeableParameter
{
private:
public:
	virtual ~AbstractChangeableParameter() {};
	// This method should change the parameter to the next value and return if the old value was the last value and so the new value is the start value again
	virtual bool switchToNextValue() = 0;
	// This method should reset the parameter to its start value
	virtual void resetToStart() = 0;
	// This method should return the value as a string for debugging purposes
	virtual std::string printCurrentValue() = 0;
};

#endif
