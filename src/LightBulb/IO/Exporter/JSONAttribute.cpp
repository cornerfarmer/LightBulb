// Includes
#include "LightBulb/IO/Exporter/JSONAttribute.hpp"

namespace LightBulb
{
	std::string JSONAttribute::toString()
	{
		return "\"" + name + "\":" + value->toString();
	}

	JSONAttribute::JSONAttribute(std::string name_, AbstractJSONElement* value_)
	{
		name = name_;
		value.reset(value_);
	}
}