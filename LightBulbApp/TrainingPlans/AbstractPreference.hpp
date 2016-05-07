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

	virtual std::string getValueAsString() = 0;
public:
	virtual ~AbstractPreference() {}

	virtual AbstractPreference* getCopy() = 0;

	AbstractPreference(std::string name_);

	std::string getName();

	std::string toString();
};

#endif
