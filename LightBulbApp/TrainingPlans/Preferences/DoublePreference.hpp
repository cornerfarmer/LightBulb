#pragma once

#ifndef _DOUBLEPREFERENCE_H_
#define _DOUBLEPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations

	class DoublePreference : public AbstractVariablePreference<double>
	{
		template <class Archive>
		friend void save(Archive& archive, DoublePreference const& doublePreference);
		template <class Archive>
		friend void load(Archive& archive, DoublePreference& doublePreference);
	protected:
		double min;
		double max;
		const std::string& getValueAsString() const override;
	public:
		DoublePreference(const std::string& name, double defaultValue, double min_, double max_);
		DoublePreference() = default;
		double getMin() const;
		double getMax() const;
		AbstractPreferenceElement* getCopy() const override;

	};
}

#include "IO/DoublePreferenceIO.hpp"

#endif
