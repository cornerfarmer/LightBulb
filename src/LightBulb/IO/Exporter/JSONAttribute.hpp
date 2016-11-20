#pragma once

#ifndef _JSONATTRIBUTE_H_
#define _JSONATTRIBUTE_H_

// Includes
#include "IO/Exporter/AbstractJSONElement.hpp"

// Library includes
#include <string>
#include <memory>

namespace LightBulb
{
	// Forward declarations
	
	// 
	class JSONAttribute
	{
	private:
		std::string name;
		std::unique_ptr<AbstractJSONElement> value;
	public:
		JSONAttribute(std::string name_, AbstractJSONElement* value_);
		std::string toString();
	};
}

#endif