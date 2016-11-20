#pragma once

#ifndef _JSONOBJECT_H_
#define _JSONOBJECT_H_

// Includes
#include "IO/Exporter/AbstractJSONElement.hpp"
#include "IO/Exporter/JSONAttribute.hpp"

// Library includes
#include <string>
#include <vector>

namespace LightBulb
{
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
}

#endif