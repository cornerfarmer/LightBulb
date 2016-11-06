// Includes
#include "IO/JSONObject.hpp"

namespace LightBulb
{
	std::string JSONObject::toString()
	{
		return "{" + attributesToString() + "}";
	}

	std::string JSONObject::attributesToString()
	{
		std::string output = "";
		for (auto attribute = attributes.begin(); attribute != attributes.end(); attribute++)
		{
			output += (*attribute)->toString();
			if (*attribute != attributes.back())
				output += ",";
		}
		return output;
	}

	void JSONObject::addAttribute(JSONAttribute* newAttribute)
	{
		attributes.push_back(std::unique_ptr<JSONAttribute>(newAttribute));
	}
}