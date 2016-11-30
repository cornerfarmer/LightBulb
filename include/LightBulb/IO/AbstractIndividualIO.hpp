#pragma once

#ifndef _ABSTRACTINDIVIDUALIO_H_
#define _ABSTRACTINDIVIDUALIO_H_

// Includes
#include "Learning/Evolution/AbstractIndividual.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractIndividual
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param individual The AbstractIndividual to save.
	 */
	template <class Archive>
	void save(Archive& archive, AbstractIndividual const& individual)
	{
		archive(cereal::make_nvp("mutationStrength", individual.mutationStrength));
	}

	/**
	* \brief Load an AbstractIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractIndividual to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractIndividual& individual)
	{
		archive(cereal::make_nvp("mutationStrength", individual.mutationStrength));
	}
}


#endif