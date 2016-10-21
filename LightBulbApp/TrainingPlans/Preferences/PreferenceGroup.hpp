#pragma once

#ifndef _PREFERENCEGROUP_H_
#define _PREFERENCEGROUP_H_

// Includes
#include "AbstractPreferenceElement.hpp"
#include "TrainingPlans/Preferences/AbstractPreference.hpp"

// Library includes
#include <memory>
#include <string>

namespace LightBulb
{
	// Forward declarations

	class PreferenceGroup : public AbstractPreferenceElement
	{
		template <class Archive>
		friend void save(Archive& archive, PreferenceGroup const& preferenceGroup);
		template <class Archive>
		friend void load(Archive& archive, PreferenceGroup& preferenceGroup);
	protected:
		std::string name;

		std::vector<std::unique_ptr<AbstractPreferenceElement>> preferences;
	public:
		virtual ~PreferenceGroup() {}

		PreferenceGroup(const std::string& name_);
		PreferenceGroup(const PreferenceGroup& other);
		PreferenceGroup() = default;

		AbstractPreferenceElement* getCopy() const override;
		const std::string& getName() const override;

		std::string toString() const override;

		void addPreference(AbstractPreferenceElement* preferenceElement);

		const AbstractPreference& getPreference(const std::string& preferenceName) const;

		PreferenceGroup& getPreferenceGroup(const std::string& preferenceGroupName) const;
		double getDoublePreference(const std::string& preferenceName) const;
		int getIntegerPreference(const std::string& preferenceName) const;
		bool getBooleanPreference(const std::string& preferenceName) const;
		std::string getChoicePreference(const std::string& preferenceName) const;

		const std::vector<std::unique_ptr<AbstractPreferenceElement>>& getPreferenceElements() const;

		template<class Class, class PreferenceGroupClass>
		Class createFromGroup() const
		{
			for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
			{
				if (dynamic_cast<PreferenceGroupClass*>(preference->get()))
					return dynamic_cast<PreferenceGroupClass*>(preference->get())->create();
			}
			throw std::logic_error("The preference group could not be found.");
		}
		template<class Class, class PreferenceGroupClass>
		Class createFromGroup(std::string groupName) const
		{
			const PreferenceGroup& preferenceGroup = getPreferenceGroup(groupName);
			if (dynamic_cast<PreferenceGroupClass&>(preferenceGroup))
				return dynamic_cast<PreferenceGroupClass&>(preferenceGroup).create();

			throw std::logic_error("The preference group could not be found.");
		}
	};
}

#include "IO/PreferenceGroupIO.hpp"

#endif
