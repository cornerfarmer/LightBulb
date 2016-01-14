#pragma once

#ifndef _JSONSTRINGELEMENT_H_
#define _JSONSTRINGELEMENT_H_

// Includes
#include "IO/AbstractJSONElement.hpp"

// Library includes
#include <string>

// Forward declarations

// 
class JSONStringElement : public AbstractJSONElement
{
private:
	std::string content;
public:
	std::string toString();
	JSONStringElement(std::string content_);
};

#endif