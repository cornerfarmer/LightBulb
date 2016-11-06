#pragma once

#ifndef _ABSTRACTEVOLUTIONOBJECTIO_H_
#define _ABSTRACTEVOLUTIONOBJECTIO_H_

// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractEvolutionObject
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param object The AbstractEvolutionObject to save.
	 */
	template <class Archive>
	void save(Archive& archive, AbstractEvolutionObject const& object)
	{
		archive(cereal::make_nvp("mutationStrength", object.mutationStrength));
	}

	/**
	* \brief Load an AbstractEvolutionObject
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param object The AbstractEvolutionObject to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractEvolutionObject& object)
	{
		archive(cereal::make_nvp("mutationStrength", object.mutationStrength));
	}
}


#endif