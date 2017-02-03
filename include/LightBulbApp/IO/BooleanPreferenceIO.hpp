#pragma once

#ifndef _BOOLEANPREFERENCEIO_H_
#define _BOOLEANPREFERENCEIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an BooleanPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param booleanPreference The BooleanPreference to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, BooleanPreference const& booleanPreference);

	/**
	* \brief Loads an BooleanPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param booleanPreference The BooleanPreference to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, BooleanPreference& booleanPreference);
}

#endif