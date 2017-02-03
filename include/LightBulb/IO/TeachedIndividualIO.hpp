#pragma once

#ifndef _TEACHEDINDIVIDUALIO_H_
#define _TEACHEDINDIVIDUALIO_H_

// Includes
#include "LightBulb/Learning/Evolution/TeachedIndividual.hpp"

namespace LightBulb
{
	/**
	* \brief Saves a TeachedIndividual.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The TeachedIndividual to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, TeachedIndividual const& individual);

	/**
	* \brief Loads a TeachedIndividual.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The TeachedIndividual to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, TeachedIndividual& individual);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(TeachedIndividual)

#endif