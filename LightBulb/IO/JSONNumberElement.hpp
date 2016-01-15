#pragma once

#ifndef _JSONNUMBERELEMENT_H_
#define _JSONNUMBERELEMENT_H_

// Includes
#include "IO/AbstractJSONElement.hpp"

// Library includes
#include <sstream>
#include <iomanip>

// Forward declarations

// 
template<typename T>
class JSONNumberElement : public AbstractJSONElement
{
private:
	T number;
public:
	JSONNumberElement(T number_)
	{
		number = number_;
	}

	std::string toString()
	{
		std::ostringstream convert;
		convert << std::fixed << std::setprecision(14) << number;
		return convert.str();
	}
};

#endif