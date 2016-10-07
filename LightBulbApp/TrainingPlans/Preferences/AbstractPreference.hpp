#pragma once

#ifndef _ABSTRACTPREFERENCE_H_
#define _ABSTRACTPREFERENCE_H_

// Includes

// Library includes
#include <string>
#include <memory>
#include <vector>

namespace LightBulb
{
	// Forward declarations

	class AbstractPreference
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractPreference const& preference);
		template <class Archive>
		friend void load(Archive& archive, AbstractPreference& preference);
	protected:
		std::string name;

		virtual std::string getValueAsString() = 0;
	public:
		virtual ~AbstractPreference() {}

		virtual AbstractPreference* getCopy() = 0;

		AbstractPreference(std::string name_);

		AbstractPreference() = default;

		std::string getName();

		std::string toString();
	};
}

#include "IO/AbstractPreferenceIO.hpp"

#endif
