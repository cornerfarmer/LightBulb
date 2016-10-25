#pragma once

#ifndef _INTEGERPREFERENCE_H_
#define _INTEGERPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	/**
	* \brief Describes a integer preference.
	*/
	class IntegerPreference : public AbstractVariablePreference<int>
	{
		template <class Archive>
		friend void save(Archive& archive, IntegerPreference const& integerPreference);
		template <class Archive>
		friend void load(Archive& archive, IntegerPreference& integerPreference);
	protected:
		/**
		* \brief The lower boundary of allowed values
		*/
		int min;
		/**
		* \brief The upper boundary of allowed values
		*/
		int max;
		// Inherited:
		std::string getValueAsString() const override;
	public:
		/**
		* \brief Creates a integer preference.
		* \param name The name.
		* \param defaultValue The default value.
		* \param min_ The lower boundary of allowed values.
		* \param max_ The upper boundary of allowed values.
		*/
		IntegerPreference(const std::string& name, int defaultValue, int min_, int max_);
		/**
		* \brief Creates a empty integer preference.
		*/
		IntegerPreference() = default;
		/**
		* \brief Returns the lower boundary of allowed values.
		* \return The minimum.
		*/
		int getMin() const;
		/**
		* \brief Returns the upper boundary of allowed values.
		* \return The maximum.
		*/
		int getMax() const;
		// Inherited:
		AbstractPreferenceElement* getCopy() const override;
	};
}

#include "IO/IntegerPreferenceIO.hpp"

#endif
