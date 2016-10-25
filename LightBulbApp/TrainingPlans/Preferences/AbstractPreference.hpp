#pragma once

#ifndef _ABSTRACTPREFERENCE_H_
#define _ABSTRACTPREFERENCE_H_

// Includes
#include "AbstractPreferenceElement.hpp"

// Library includes
#include <string>

namespace LightBulb
{
	/**
	 * \brief Describes a single preference.
	 */
	class AbstractPreference : public AbstractPreferenceElement
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractPreference const& preference);
		template <class Archive>
		friend void load(Archive& archive, AbstractPreference& preference);
	protected:
		/**
		 * \brief The name of the preference.
		 */
		std::string name;
		/**
		 * \brief Returns the value as a string.
		 * \return The string.
		 */
		virtual std::string getValueAsString() const = 0;
	public:
		virtual ~AbstractPreference() {}
		/**
		 * \brief Creates a preference.
		 * \param name_ The name of the preference.
		 */
		AbstractPreference(std::string name_);
		/**
		 * \brief Creates a empty preference.
		 */
		AbstractPreference() = default;
		// Inherited:
		const std::string& getName() const override;
		std::string toString() const override;
	};
}

#include "IO/AbstractPreferenceIO.hpp"

#endif
