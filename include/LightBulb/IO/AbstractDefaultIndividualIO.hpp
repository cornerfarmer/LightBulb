#pragma once

#ifndef _ABSTRACTDEFAULTINDIVIDUALIO_H_
#define _ABSTRACTDEFAULTINDIVIDUALIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractDefaultIndividual.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractDefaultIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractDefaultIndividual to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractDefaultIndividual const& individual);

	/**
	* \brief Loads an AbstractDefaultIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractDefaultIndividual to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractDefaultIndividual& individual);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(AbstractDefaultIndividual)

#endif