#pragma once

#ifndef _BOOLEANPREFERENCE_H_
#define _BOOLEANPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	/**
	 * \brief Describes a boolean preference.
	 */
	class BooleanPreference : public AbstractVariablePreference<bool>
	{
		template <class Archive>
		friend void save(Archive& archive, BooleanPreference const& booleanPreference);
		template <class Archive>
		friend void load(Archive& archive, BooleanPreference& booleanPreference);
	protected:
		// Inherited:
		std::string getValueAsString() const override;
	public:
		/**
		 * \brief Creates a boolean preference.
		 * \param name The name.
		 * \param defaultValue The defaul value.
		 */
		BooleanPreference(const std::string& name, bool defaultValue);
		/**
		 * \brief Creates a empty boolean preference.
		 */
		BooleanPreference() = default;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

#include "IO/BooleanPreferenceIO.hpp"

#endif
