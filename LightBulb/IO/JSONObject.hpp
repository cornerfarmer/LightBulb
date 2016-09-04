#pragma once

#ifndef _JSONOBJECT_H_
#define _JSONOBJECT_H_

// Includes
#include "IO/AbstractJSONElement.hpp"
#include "IO/JSONAttribute.hpp"

// Library includes
#include <string>
#include <vector>

// Forward declarations

// 
class JSONObject : public AbstractJSONElement
{
private:
	std::vector<std::unique_ptr<JSONAttribute>> attributes;
	std::string attributesToString();
public:
	std::string toString() override;
	void addAttribute(JSONAttribute* newAttribute);
};

#endif