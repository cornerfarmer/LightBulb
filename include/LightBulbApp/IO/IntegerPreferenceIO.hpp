#pragma once

#ifndef _INTEGERPREFERENCEIO_H_
#define _INTEGERPREFERENCEIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an IntegerPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param integerPreference The IntegerPreference to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, IntegerPreference const& integerPreference);

	/**
	* \brief Loads an IntegerPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param integerPreference The IntegerPreference to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, IntegerPreference& integerPreference);
}

#endif