// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/ChoicePreference.hpp"

namespace LightBulb
{
	ChoicePreference::ChoicePreference(const std::string& name, const std::string& defaultValue)
		:AbstractVariablePreference(name, defaultValue)
	{

	}

	void ChoicePreference::addChoice(const std::string& newChoice)
	{
		choices.push_back(newChoice);
	}

	void ChoicePreference::setValueFromIndex(int index)
	{
		setValue(choices[index]);
	}

	int ChoicePreference::getValueAsIndex() const
	{
		return std::find(choices.begin(), choices.end(), getValue()) - choices.begin();
	}

	const std::vector<std::string>& ChoicePreference::getChoices() const
	{
		return choices;
	}

	AbstractCloneable* ChoicePreference::clone() const
	{
		return new ChoicePreference(*this);
	}

	std::string ChoicePreference::getValueAsString() const
	{
		return value;
	}
}
