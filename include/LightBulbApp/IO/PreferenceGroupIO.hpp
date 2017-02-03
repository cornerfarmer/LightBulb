#pragma once

#ifndef _PREFERENCEGROUPIO_H_
#define _PREFERENCEGROUPIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"

namespace LightBulb
{
	/**
	* \brief Saves a PreferenceGroup.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preferenceGroup The PreferenceGroup to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, PreferenceGroup const& preferenceGroup);

	/**
	* \brief Loads a PreferenceGroup.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preferenceGroup The PreferenceGroup to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, PreferenceGroup& preferenceGroup);
}

#endif