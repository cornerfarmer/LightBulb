#pragma once

#ifndef _ABSTRACTDEFAULTINDIVIDUALIO_H_
#define _ABSTRACTDEFAULTINDIVIDUALIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractDefaultIndividual.hpp"
#include "LightBulb/IO/IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractDefaultIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractDefaultIndividual to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractDefaultIndividual const& individual)
	{
		archive(cereal::base_class<AbstractIndividual>(&individual));
		archive(cereal::make_nvp("neuralNetwork", individual.neuralNetwork));
	}

	/**
	* \brief Loads an AbstractDefaultIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractDefaultIndividual to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractDefaultIndividual& individual)
	{
		archive(cereal::base_class<AbstractIndividual>(&individual));
		archive(cereal::make_nvp("neuralNetwork", individual.neuralNetwork));
		individual.environment = IOStorage<AbstractEvolutionEnvironment>::get();
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractDefaultIndividual);

#endif