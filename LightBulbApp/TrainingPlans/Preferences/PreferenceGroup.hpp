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

		PreferenceGroup(std::string name_);
		PreferenceGroup(const PreferenceGroup& other);
		PreferenceGroup() = default;

		AbstractPreferenceElement* getCopy() override;
		std::string getName() override;

		std::string toString() override;

		void addPreference(AbstractPreferenceElement* preferenceElement);

		AbstractPreference* getPreference(std::string preferenceName);

		PreferenceGroup* getPreferenceGroup(std::string preferenceGroupName);
		double getDoublePreference(std::string preferenceName);
		int getIntegerPreference(std::string preferenceName);
		bool getBooleanPreference(std::string preferenceName);

		std::vector<std::unique_ptr<AbstractPreferenceElement>>& getPreferenceElements();

		template<class Class, class PreferenceGroupClass>
		Class createFromGroup()
		{
			for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
			{
				if (dynamic_cast<PreferenceGroupClass*>(preference->get()))
					return dynamic_cast<PreferenceGroupClass*>(preference->get())->create();
			}
			throw std::logic_error("The preference group could not be found.");
		}
		template<class Class, class PreferenceGroupClass>
		Class createFromGroup(std::string groupName)
		{
			PreferenceGroup* preferenceGroup = getPreferenceGroup(groupName);
			if (dynamic_cast<PreferenceGroupClass*>(preferenceGroup))
				return dynamic_cast<PreferenceGroupClass*>(preferenceGroup)->create();

			throw std::logic_error("The preference group could not be found.");
		}
	};
}

#include "IO/PreferenceGroupIO.hpp"

#endif
