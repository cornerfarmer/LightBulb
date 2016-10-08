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
		std::string getValueAsString() override;
	public:
		IntegerPreference(std::string name, int defaultValue, int min_, int max_);
		IntegerPreference() = default;
		int getMin();
		int getMax();
		AbstractPreferenceElement* getCopy() override;
	};
}

#include "IO/IntegerPreferenceIO.hpp"

#endif
