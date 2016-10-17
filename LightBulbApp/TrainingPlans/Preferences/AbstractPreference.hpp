#pragma once

#ifndef _ABSTRACTPREFERENCE_H_
#define _ABSTRACTPREFERENCE_H_

// Includes
#include "AbstractPreferenceElement.hpp"

// Library includes
#include <string>
#include <memory>
#include <vector>

namespace LightBulb
{
	// Forward declarations

	class AbstractPreference : public AbstractPreferenceElement
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractPreference const& preference);
		template <class Archive>
		friend void load(Archive& archive, AbstractPreference& preference);
	protected:
		std::string name;

		virtual std::string getValueAsString() const = 0;
	public:
		virtual ~AbstractPreference() {}

		AbstractPreference(std::string name_);

		AbstractPreference() = default;

		const std::string& getName() const override;

		std::string toString() const override;
	};
}

#include "IO/AbstractPreferenceIO.hpp"

#endif
