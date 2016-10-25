#pragma once

#ifndef _ABSTRACTVARIABLEPREFERENCE_H_
#define _ABSTRACTVARIABLEPREFERENCE_H_

// Includes
#include "AbstractPreference.hpp"

// Library includes

namespace LightBulb
{
	/**
	 * \brief Describes a preference which only contains one value of one specific data type.
	 * \tparam Type The data type the preference value should have.
	 */
	template<class Type>
	class AbstractVariablePreference : public AbstractPreference
	{
	protected:
		/**
		 * \brief The current value of the preference.
		 */
		Type value;
		/**
		 * \brief The default value of the preference.
		 */
		Type defaultValue;
	public:
		/**
		 * \brief Creates a variable preference.
		 * \param name The name.
		 * \param defaultValue_ The default value.
		 */
		AbstractVariablePreference(const std::string& name, Type defaultValue_)
			:AbstractPreference(name)
		{
			defaultValue = defaultValue_;
			reset();
		}
		/**
		 * \brief Creates a empty variable preference.
		 */
		AbstractVariablePreference()
		{
		}
		/**
		 * \brief Sets the value.
		 * \param newValue The new value.
		 */
		void setValue(Type newValue)
		{
			value = newValue;
		}
		/**
		 * \brief Returns the current value.
		 * \return The current value.
		 */
		Type getValue() const
		{
			return value;
		}
		/**
		 * \brief Resets the value back to its default value.
		 */
		void reset()
		{
			value = defaultValue;
		}
	};
}

#endif
