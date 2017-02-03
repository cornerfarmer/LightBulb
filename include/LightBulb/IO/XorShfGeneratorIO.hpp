#pragma once

#ifndef _XORSHFGENERATORIO_H_
#define _XORSHFGENERATORIO_H_

// Includes
#include "LightBulb/Random/XorShfGenerator.hpp"

namespace LightBulb
{
	/**
	* \brief Saves a XorShfGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param xorShfGenerator The XorShfGenerator to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, XorShfGenerator const& xorShfGenerator);

	/**
	* \brief Loads a XorShfGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param xorShfGenerator The XorShfGenerator to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, XorShfGenerator& xorShfGenerator);
}

#endif