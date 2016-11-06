// Includes
#include "IO/JSONArray.hpp"

namespace LightBulb
{
	std::string JSONArray::toString()
	{
		return "[" + elementsToString() + "]";
	}

	std::string JSONArray::elementsToString()
	{
		std::string output = "";
		for (auto element = elements.begin(); element != elements.end(); element++)
		{
			output += (*element)->toString();
			if (*element != elements.back())
				output += ",";
		}
		return output;
	}

	void JSONArray::addElement(AbstractJSONElement* newElement)
	{
		elements.push_back(std::unique_ptr<AbstractJSONElement>(newElement));
	}
}