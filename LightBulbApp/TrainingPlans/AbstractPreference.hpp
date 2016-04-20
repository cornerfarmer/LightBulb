#pragma once

#ifndef _ABSTRACTPREFERENCE_H_
#define _ABSTRACTPREFERENCE_H_

// Includes

// Library includes
#include <string>
#include <memory>
#include <vector>

// Forward declarations

class AbstractPreference
{
protected:
	std::string name;
public:
	virtual ~AbstractPreference() {}

	virtual AbstractPreference* getCopy() = 0;

	AbstractPreference(std::string name_)
	{
		name = name_;
	}

	std::string getName()
	{
		return name;
	}
};

#endif
