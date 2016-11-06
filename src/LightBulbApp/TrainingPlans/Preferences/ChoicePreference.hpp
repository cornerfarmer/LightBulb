#pragma once

#ifndef _CHOICEPREFERENCE_H_
#define _CHOICEPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	/**
	 * \brief Describes a string preference, whosen value can be chosen between multiple options.
	 */
	class ChoicePreference : public AbstractVariablePreference<std::string>
	{
		template <class Archive>
		friend void save(Archive& archive, ChoicePreference const& choicePreference);
		template <class Archive>
		friend void load(Archive& archive, ChoicePreference& choicePreference);
	protected:
		/**
		 * \brief The possible values.
		 */
		std::vector<std::string> choices;
		// Inherited:
		std::string getValueAsString() const override;
	public:
		/**
		 * \brief Creates a choice preference.
		 * \param name The name.
		 * \param defaultValue The default value.
		 */
		ChoicePreference(const std::string& name, const std::string& defaultValue);
		/**
		 * \brief Creates a empty choice preference.
		 */
		ChoicePreference() = default;
		/**
		 * \brief Adds a new choice the possible values.
		 * \param newChoice The new choice.
		 */
		void addChoice(const std::string& newChoice);
		/**
		 * \brief Sets the value from the choice with the given index.
		 * \param index The index to use.
		 */
		void setValueFromIndex(int index);
		/**
		 * \brief Returns the index of the current value in the storage vector.
		 * \return The index.
		 */
		int getValueAsIndex() const;
		/**
		 * \brief Returns all possible choices.
		 * \return The vector of choices.
		 */
		const std::vector<std::string>& getChoices() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

#include "IO/IntegerPreferenceIO.hpp"

#endif
