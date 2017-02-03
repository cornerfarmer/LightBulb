#pragma once

#ifndef _ZIGGURATGENERATORIO_H_
#define _ZIGGURATGENERATORIO_H_

// Includes
#include "LightBulb/Random/ZigguratGenerator.hpp"

namespace LightBulb
{
	/**
	* \brief Saves a ZigguratGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param zigguratGenerator The ZigguratGenerator to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, ZigguratGenerator const& zigguratGenerator);

	/**
	* \brief Loads a ZigguratGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param zigguratGenerator The ZigguratGenerator to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, ZigguratGenerator& zigguratGenerator);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(ZigguratGenerator)

#endif