#pragma once

#ifndef _CHOICEPREFERENCEIO_H_
#define _CHOICEPREFERENCEIO_H_

// Includes
#include "TrainingPlans/Preferences/ChoicePreference.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	template <class Archive>
	void save(Archive& archive, ChoicePreference const& choicePreference)
	{
		archive(cereal::base_class<AbstractPreference>(&choicePreference));
		archive(cereal::make_nvp("value", choicePreference.value));
	}

	template <class Archive>
	void load(Archive& archive, ChoicePreference& choicePreference)
	{
		archive(cereal::base_class<AbstractPreference>(&choicePreference));
		archive(cereal::make_nvp("value", choicePreference.value));
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::ChoicePreference);

#endif