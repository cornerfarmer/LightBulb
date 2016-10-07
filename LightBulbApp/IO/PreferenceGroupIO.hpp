#pragma once

#ifndef _PREFERENCEGROUPIO_H_
#define _PREFERENCEGROUPIO_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	template <class Archive>
	void save(Archive& archive, PreferenceGroup const& preferenceGroup)
	{
		archive(cereal::make_nvp("preferences", preferenceGroup.preferences));
	}

	template <class Archive>
	void load(Archive& archive, PreferenceGroup& preferenceGroup)
	{
		archive(cereal::make_nvp("preferences", preferenceGroup.preferences));
	}
}

#endif