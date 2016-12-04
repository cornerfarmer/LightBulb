#pragma once

#ifndef _DOUBLEPREFERENCE_H_
#define _DOUBLEPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	/**
	* \brief Describes a double preference.
	*/
	class DoublePreference : public AbstractVariablePreference<double>
	{
		template <class Archive>
		friend void save(Archive& archive, DoublePreference const& doublePreference);
		template <class Archive>
		friend void load(Archive& archive, DoublePreference& doublePreference);
	protected:
		/**
		 * \brief The lower boundary of allowed values
		 */
		double min;
		/**
		* \brief The upper boundary of allowed values
		*/
		double max;
		// Inherited:
		std::string getValueAsString() const override;
	public:
		/**
		* \brief Creates a double preference.
		* \param name The name.
		* \param defaultValue The default value.
		* \param min_ The lower boundary of allowed values.
		* \param max_ The upper boundary of allowed values.
		*/
		DoublePreference(const std::string& name, double defaultValue, double min_, double max_);
		/**
		 * \brief Creates a empty double preference.
		 */
		DoublePreference() = default;
		/**
		 * \brief Returns the lower boundary of allowed values.
		 * \return The minimum.
		 */
		double getMin() const;
		/**
		* \brief Returns the upper boundary of allowed values.
		* \return The maximum.
		*/
		double getMax() const;
		// Inherited:
		AbstractCloneable* clone() const override;

	};
}

#include "LightBulbApp/IO/DoublePreferenceIO.hpp"

#endif
