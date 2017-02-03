#pragma once

#ifndef _ABSTRACTPREFERENCEIO_H_
#define _ABSTRACTPREFERENCEIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/AbstractPreference.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preference The AbstractPreference to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractPreference const& preference);

	/**
	* \brief Loads an AbstractPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preference The AbstractPreference to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractPreference& preference);
}


#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(AbstractPreference)

#endif