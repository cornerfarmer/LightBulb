#pragma once

#ifndef _CHOICEPREFERENCE_H_
#define _CHOICEPREFERENCE_H_

// Includes
#include "AbstractVariablePreference.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations

	class ChoicePreference : public AbstractVariablePreference<std::string>
	{
		template <class Archive>
		friend void save(Archive& archive, ChoicePreference const& choicePreference);
		template <class Archive>
		friend void load(Archive& archive, ChoicePreference& choicePreference);
	protected:
		std::vector<std::string> choices;
		std::string getValueAsString() const override;
	public:
		ChoicePreference(const std::string& name, const std::string& defaultValue);
		ChoicePreference() = default;
		void addChoice(const std::string& newChoice);
		void setValueFromIndex(int index);
		int getValueAsIndex() const;
		const std::vector<std::string>& getChoices() const;
		AbstractPreferenceElement* getCopy() const override;
	};
}

#include "IO/IntegerPreferenceIO.hpp"

#endif
