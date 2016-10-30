#pragma once

#ifndef _ABSTRACTPREFERENCEELEMENT_H_
#define _ABSTRACTPREFERENCEELEMENT_H_

// Includes
#include "IO/UseParentSerialization.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library includes
#include <string>

namespace LightBulb
{
	// Forward declarations

	/**
	 * \brief Describes a preference element. Can be a single preference or a preference group.
	 */
	class AbstractPreferenceElement : public virtual AbstractCloneable
	{
	protected:
	public:
		virtual ~AbstractPreferenceElement() {}
		/**
		 * \brief Generates a string which describes the current state of the element in human readable format.
		 * \return The string.
		 */
		virtual std::string toString() const = 0;
		/**
		 * \brief Returns the name of the element.
		 * \return The name.
		 */
		virtual const std::string& getName() const = 0;
	};
}

EMPTY_SERIALIZATION(LightBulb::AbstractPreferenceElement, LightBulb);

#endif
