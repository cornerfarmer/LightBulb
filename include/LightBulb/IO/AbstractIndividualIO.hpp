#pragma once

#ifndef _ABSTRACTINDIVIDUALIO_H_
#define _ABSTRACTINDIVIDUALIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractIndividual
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param individual The AbstractIndividual to save.
	 */
	template <class Archive>
	extern void save(Archive& archive, AbstractIndividual const& individual);

	/**
	* \brief Load an AbstractIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractIndividual to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractIndividual& individual);
}


#endif