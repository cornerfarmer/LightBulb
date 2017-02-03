#pragma once

#ifndef _ABSTRACTRANDOMGENERATORIO_H_
#define _ABSTRACTRANDOMGENERATORIO_H_

// Includes
#include "LightBulb/Random/AbstractRandomGenerator.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractRandomGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param randomGenerator The AbstractRandomGenerator to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractRandomGenerator const& randomGenerator);

	/**
	* \brief Loads an AbstractRandomGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param randomGenerator The AbstractRandomGenerator to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractRandomGenerator& randomGenerator);
}

#endif