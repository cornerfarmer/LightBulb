#pragma once

#ifndef _CHOICEPREFERENCEIO_H_
#define _CHOICEPREFERENCEIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/ChoicePreference.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an ChoicePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param choicePreference The ChoicePreference to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, ChoicePreference const& choicePreference);

	/**
	* \brief Loads an ChoicePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param choicePreference The ChoicePreference to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, ChoicePreference& choicePreference);
}

#endif