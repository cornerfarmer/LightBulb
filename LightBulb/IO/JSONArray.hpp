#pragma once

#ifndef _JSONARRAY_H_
#define _JSONARRAY_H_

// Includes 
#include "IO/AbstractJSONElement.hpp"

// Library includes
#include <vector>

// Forward declarations

// 
class JSONArray : public AbstractJSONElement
{
private:
	std::vector<std::unique_ptr<AbstractJSONElement>> elements;
	std::string elementsToString();
public:
	std::string toString();
	void addElement(AbstractJSONElement* newElement);
};

#endif