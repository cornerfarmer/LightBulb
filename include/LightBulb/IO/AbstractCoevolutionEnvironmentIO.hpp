#pragma once

#ifndef _ABSTRACTCOEVOLUTIONENVIRONMENTIO_H_
#define _ABSTRACTCOEVOLUTIONENVIRONMENTIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractCoevolutionEnvironment
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param environment The AbstractCoevolutionEnvironment to save.
	 */
	template <class Archive>
	extern void save(Archive& archive, AbstractCoevolutionEnvironment const& environment);


	/**
	* \brief Loads an AbstractCoevolutionEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractCoevolutionEnvironment to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractCoevolutionEnvironment& environment);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(AbstractCoevolutionEnvironment)


#endif