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

		virtual std::string toString() const = 0;

		virtual const std::string& getName() const = 0;

		virtual AbstractPreferenceElement* getCopy() const = 0;
	};
}

EMPTY_SERIALIZATION(LightBulb::AbstractPreferenceElement, LightBulb);

#endif
