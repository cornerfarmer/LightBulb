#pragma once

#ifndef _PREFERENCEGROUPIO_H_
#define _PREFERENCEGROUPIO_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	template <class Archive>
	void save(Archive& archive, PreferenceGroup const& preferenceGroup)
	{
		archive(cereal::base_class<AbstractPreferenceElement>(&preferenceGroup));
		archive(cereal::make_nvp("preferences", preferenceGroup.preferences));
	}

	template <class Archive>
	void load(Archive& archive, PreferenceGroup& preferenceGroup)
	{
		archive(cereal::base_class<AbstractPreferenceElement>(&preferenceGroup));
		archive(cereal::make_nvp("preferences", preferenceGroup.preferences));
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::PreferenceGroup);

#endif