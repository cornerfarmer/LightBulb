// Includes
#include "IO/JSONAttribute.hpp"

std::string JSONAttribute::toString()
{
	return "\"" + name + "\":" + value->toString();
}

JSONAttribute::JSONAttribute(std::string name_, AbstractJSONElement* value_)
{
	name = name_;
	value.reset(value_);
}
