#pragma once

#ifndef _PREFERENCEGROUP_H_
#define _PREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/AbstractPreference.hpp"

// Library includes
#include <memory>
#include <string>

namespace LightBulb
{
	// Forward declarations

	class PreferenceGroup
	{
		template <class Archive>
		friend void save(Archive& archive, PreferenceGroup const& preferenceGroup);
		template <class Archive>
		friend void load(Archive& archive, PreferenceGroup& preferenceGroup);
	protected:
		std::string name;

		std::vector<std::unique_ptr<AbstractPreference>> preferences;
	public:
		PreferenceGroup* getCopy();

		PreferenceGroup(std::string name_);

		PreferenceGroup() = default;

		std::string getName();

		std::string toString();

		void addPreference(AbstractPreference* preference);

		AbstractPreference* getPreference(std::string name);

		std::vector<std::unique_ptr<AbstractPreference>>& getPreferences();
	};
}

#include "IO/PreferenceGroupIO.hpp"

#endif
