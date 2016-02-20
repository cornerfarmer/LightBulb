// Includes
#include "IO/JSONStringElement.hpp"

std::string JSONStringElement::toString()
{
	return "\"" + content + "\"";
}

JSONStringElement::JSONStringElement(std::string content_)
{
	content = content_;
}