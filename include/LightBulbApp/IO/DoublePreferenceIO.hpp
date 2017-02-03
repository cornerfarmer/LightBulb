#pragma once

#ifndef _DOUBLEPREFERENCEIO_H_
#define _DOUBLEPREFERENCEIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an DoublePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param doublePreference The DoublePreference to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, DoublePreference const& doublePreference);

	/**
	* \brief Loads an DoublePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param doublePreference The DoublePreference to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, DoublePreference& doublePreference);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(DoublePreference)

#endif