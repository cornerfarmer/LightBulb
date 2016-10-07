#pragma once

#ifndef _ABSTRACTVARIABLEPREFERENCE_H_
#define _ABSTRACTVARIABLEPREFERENCE_H_

// Includes
#include "AbstractPreference.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations

	template<class Type>
	class AbstractVariablePreference : public AbstractPreference
	{
	protected:
		Type value;
		Type defaultValue;
	public:
		AbstractVariablePreference(std::string name, Type defaultValue_)
			:AbstractPreference(name)
		{
			defaultValue = defaultValue_;
			reset();
		}

		AbstractVariablePreference()
		{
		}

		void setValue(Type newValue)
		{
			value = newValue;
		}

		Type getValue()
		{
			return value;
		}

		void reset()
		{
			value = defaultValue;
		}
	};
}

#endif
