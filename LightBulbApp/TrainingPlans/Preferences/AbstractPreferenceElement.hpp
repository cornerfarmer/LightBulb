#pragma once

#ifndef _ABSTRACTPREFERENCEELEMENT_H_
#define _ABSTRACTPREFERENCEELEMENT_H_

// Includes
#include "IO/UseParentSerialization.hpp"

// Library includes
#include <string>

namespace LightBulb
{
	// Forward declarations

	class AbstractPreferenceElement
	{
	protected:
	public:
		virtual ~AbstractPreferenceElement() {}

		virtual std::string toString() = 0;

		virtual std::string getName() = 0;

		virtual AbstractPreferenceElement* getCopy() = 0;
	};
}

EMPTY_SERIALIZATION(LightBulb::AbstractPreferenceElement, LightBulb);

#endif
