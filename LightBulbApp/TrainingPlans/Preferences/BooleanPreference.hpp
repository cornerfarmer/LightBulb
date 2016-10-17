#pragma once

#ifndef _BOOLEANPREFERENCE_H_
#define _BOOLEANPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations

	class BooleanPreference : public AbstractVariablePreference<bool>
	{
		template <class Archive>
		friend void save(Archive& archive, BooleanPreference const& booleanPreference);
		template <class Archive>
		friend void load(Archive& archive, BooleanPreference& booleanPreference);
	protected:
		std::string getValueAsString() const override;
	public:
		BooleanPreference(const std::string& name, bool defaultValue);
		BooleanPreference() = default;
		AbstractPreferenceElement* getCopy() const override;
	};
}

#include "IO/BooleanPreferenceIO.hpp"

#endif
