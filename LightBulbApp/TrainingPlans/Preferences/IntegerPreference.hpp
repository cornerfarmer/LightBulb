#pragma once

#ifndef _INTEGERPREFERENCE_H_
#define _INTEGERPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations

	class IntegerPreference : public AbstractVariablePreference<int>
	{
		template <class Archive>
		friend void save(Archive& archive, IntegerPreference const& integerPreference);
		template <class Archive>
		friend void load(Archive& archive, IntegerPreference& integerPreference);
	protected:
		int min;
		int max;
		std::string getValueAsString() const override;
	public:
		IntegerPreference(const std::string& name, int defaultValue, int min_, int max_);
		IntegerPreference() = default;
		int getMin() const;
		int getMax() const;
		AbstractPreferenceElement* getCopy() const override;
	};
}

#include "IO/IntegerPreferenceIO.hpp"

#endif
