#pragma once

#ifndef _DOUBLEPREFERENCEIO_H_
#define _DOUBLEPREFERENCEIO_H_

// Includes
#include "TrainingPlans/Preferences/DoublePreference.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an DoublePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param doublePreference The DoublePreference to save.
	*/
	template <class Archive>
	void save(Archive& archive, DoublePreference const& doublePreference)
	{
		archive(cereal::base_class<AbstractPreference>(&doublePreference));
		archive(cereal::make_nvp("value", doublePreference.value));
	}

	/**
	* \brief Loads an DoublePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param doublePreference The DoublePreference to load.
	*/
	template <class Archive>
	void load(Archive& archive, DoublePreference& doublePreference)
	{
		archive(cereal::base_class<AbstractPreference>(&doublePreference));
		archive(cereal::make_nvp("value", doublePreference.value));
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::DoublePreference);

#endif