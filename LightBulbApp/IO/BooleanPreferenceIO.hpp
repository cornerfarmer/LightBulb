#pragma once

#ifndef _BOOLEANPREFERENCEIO_H_
#define _BOOLEANPREFERENCEIO_H_

// Includes
#include "TrainingPlans/Preferences/BooleanPreference.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	template <class Archive>
	void save(Archive& archive, BooleanPreference const& booleanPreference)
	{
		archive(cereal::base_class<AbstractPreference>(&booleanPreference));
		archive(cereal::make_nvp("value", booleanPreference.value));
	}

	template <class Archive>
	void load(Archive& archive, BooleanPreference& booleanPreference)
	{
		archive(cereal::base_class<AbstractPreference>(&booleanPreference));
		archive(cereal::make_nvp("value", booleanPreference.value));
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::BooleanPreference);

#endif