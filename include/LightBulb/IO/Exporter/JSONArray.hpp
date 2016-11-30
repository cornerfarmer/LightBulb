#pragma once

#ifndef _JSONARRAY_H_
#define _JSONARRAY_H_

// Includes 
#include "IO/Exporter/AbstractJSONElement.hpp"

// Library includes
#include <vector>
#include <memory>

namespace LightBulb
{
	// Forward declarations

	// 
	class JSONArray : public AbstractJSONElement
	{
	private:
		std::vector<std::unique_ptr<AbstractJSONElement>> elements;
		std::string elementsToString();
	public:
		std::string toString() override;
		void addElement(AbstractJSONElement* newElement);
	};
}

#endif