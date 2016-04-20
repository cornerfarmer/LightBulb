#pragma once

#ifndef _ABSTRACTVARIABLEPREFERENCE_H_
#define _ABSTRACTVARIABLEPREFERENCE_H_

// Includes
#include "AbstractPreference.hpp"

// Library includes

// Forward declarations

template<class Type>
class AbstractVariablePreference : public AbstractPreference
{
protected:
	Type value;
public:
	AbstractVariablePreference(std::string name, Type defaultValue)
		:AbstractPreference(name)
	{
		value = defaultValue;
	}

	void setValue(Type newValue)
	{
		value = newValue;
	}

	Type getValue()
	{
		return value;
	}
};

#endif
