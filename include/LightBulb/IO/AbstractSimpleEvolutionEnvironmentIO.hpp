#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONENVIRONMENTIO_H_
#define _ABSTRACTSIMPLEEVOLUTIONENVIRONMENTIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractSimpleEvolutionEnvironment.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractSimpleEvolutionEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractSimpleEvolutionEnvironment to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractSimpleEvolutionEnvironment const& environment);

	/**
	* \brief Loads an AbstractSimpleEvolutionEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractSimpleEvolutionEnvironment to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractSimpleEvolutionEnvironment& environment);
}

#endif
